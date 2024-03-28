%% 2RC Thevenin Model Parameter Estimation using PSO
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Load Current and Voltage Data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc; clear variables; close all;
BatteryType="SLA";
if(BatteryType=="SLA")
    Battery=loadMatDataset("SLA_Characterization_test.mat");
    tau_max=3500;
elseif(BatteryType=="LFP")
    Battery=loadMatDataset("LFP_Characterization_test.mat");
    tau_max=3500;
elseif (BatteryType=="NMC")
     Battery=loadMatDataset("03-11-17_08.47 25degC_5Pulse_HPPC_Pan18650PF.mat");
     tau_max=1100;
end
% Battery=loadMatDataset("03-11-17_08.47 25degC_5Pulse_HPPC_Pan18650PF.mat");
% Get pulse points
[Relax, Stress] = getPulsePoints(Battery.Current, Battery.Time);
Relax(1,:)=[];
RelaxV = [Relax(:,1);Relax(:,2)]; %Reshaping into a 1 column vector
StressV = [Stress(:,1);Stress(:,2)]; %Reshaping into a 1 column vector
number_of_pulses=length(Stress);
number_of_RC = 2;
%% Get Pulses
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Create an structure that will contains al points
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
number_of_pulses = length(Stress);
Pulses(number_of_pulses,1)= struct('Relax',[],'Stress',[],'Voltage',[],'Current',[],'Time',[],'SoC',[]);
OCV = zeros(1,number_of_pulses);
Rt= OCV;
Vocv0=Battery.Voltage(Stress(1,1)-1);
SOC_LUT = zeros(number_of_pulses,1);
for k=1:number_of_pulses
    pulse_start = Stress(k,1)-1;
    indexes = pulse_start:Relax(k,2);
    Pulses(k)=ProcessPulse(Battery,pulse_start,indexes,Relax(k),Stress(k));
    graph=0;
    if(graph)
        figure();
        subplot(3,1,1);
        plot(Pulses(k).Time,Pulses(k).Voltage);
        subplot(3,1,2);
        plot(Pulses(k).Time,Pulses(k).Current);
        subplot(3,1,3);
        plot(Pulses(k).Time,Pulses(k).SoC);
    end
    %% Save Rt and OCV.
    dV = Battery.Voltage(pulse_start)-Battery.Voltage(pulse_start+1);
    dI=  Battery.Current(pulse_start)-Battery.Current(pulse_start+1);
    Rt(k) = abs(dV/dI);
    SOC_LUT(k) = Pulses(k).SoC(1);
    OCV(k) = Battery.Voltage(pulse_start);
end


%% Parameter Estimation
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initialize parameter vector
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
tic
R1=zeros(number_of_pulses,1);
R2=R1;
Rt=R1;
C1=R1;
C2=R2;
RC=zeros(2,number_of_RC);
for k=1:number_of_pulses
    voltage= Pulses(k).Voltage;
    current = -Pulses(k).Current;
    time= Pulses(k).Time;
    SoC = Pulses(k).SoC;
    Ts = 1e-1;
    time_int= [0:Ts:time(end)]';
    voltage_int=interp1(time,voltage,time_int,"linear");
    current_int=interp1(time,current,time_int,"linear");
    SoC_int = interp1(time,SoC,time_int,"linear");
    ocv_int = interp1(SOC_LUT,OCV,SoC_int,"linear",'extrap');
    if(BatteryType=="LFP")
        %for more precision we use the "continuos" OCV vs SoC Curve.
        load("Li_ion_Vocv.mat");
        ocv_int = interp1(SOC_EST,Vocv,SoC_int,"linear",'extrap');
    end
    % i. Get Vdiff=vt-OCV+Rt*I= -Vc1-Vc2;
    Vdiff = voltage_int-ocv_int;%+Rt(1)*current_int;
    ttVdiff = timetable(current_int,Vdiff,'TimeStep',seconds(Ts));
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Estimate RC Pair using Subspace State Space system Identifiaction n4sid
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    order = number_of_RC;
    while 1
        RC_pairs = n4sid(current_int,Vdiff,order,'Ts',Ts); % Matrices must be column matrices
        %compare([current_int],[Vdiff],RC_pairs);
        RCfact = sort(eig(RC_pairs.A)); % Order the RC factors
        inRange = length(RCfact(RCfact>0 & RCfact<1)); % Let's see if the RCfacts are under 1

        if(isreal(RCfact) && inRange >= number_of_RC)
            break; %RC fact is in range and is real
        else
            order = order+1; % Let's try with a model with more RC branches
        end

    end

    if(order>number_of_RC)
        RCfact = RCfact(end-number_of_RC+1:end);
        %If the estimation was performed with more than 2 RC branches
        % Let's take only the last 2 RC_factors of the diagonal.
    end
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Simulate to get Capacitor currents in = A*[i1,i2]+B*I
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    RCModel = ss(diag(RCfact),1-RCfact,eye(2),0,Ts);
    [ik]=lsim(RCModel,current_int,time_int,[0 0]);
    i1=ik(:,1); i2=ik(:,2);


    %% Least Square method
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % We have Vdiff = [-i1 -i2 -current]*[R1;
    %                                      R2;
    %                                      Rt]
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Solve Ls using lsqnonneg
    %     x=lsqnonneg([-i1 -i2 -current_int],Vdiff);
    x = lsqlin([-i1 -i2 -current_int],Vdiff,[],[],[],[],ones(3)*1e-5,ones(3)*Inf);
    R1(k)=x(1);
    R2(k)=x(2);
    Rt(k)=x(3);
    RC(:,k) = RCfact;
    C1(k) = -Ts/(log(RCfact(1))*R1(k));
    C2(k) = -Ts/(log(RCfact(2))*R2(k));
    RCModel = ss(diag(RCfact),(1-RCfact).*[R1(k);R2(k)],[-1 -1],0,Ts);
    [RCv,t]=lsim(RCModel,current_int,time_int,[0 0]);
    graph=0;
    if(graph)
        figure();
        plot(time_int,Vdiff);
        hold on;
        plot(t,RCv,"--");
        hold off;
    end
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %% Complete system simulation
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Vt=ocv_int+RCv-Rt(k)*current_int;
    disp("Initial RMSE="+num2str(rmse(Vt,voltage_int)));
    graph=0;
    if(graph)
        figure();
        plot(time_int,Vt);
        hold on;
        plot(time_int,voltage_int);
    end
    RMSError=rmse(Vt,voltage_int);
    


    %% Particle Swarm Optimization
    % complete system simulation using the previously found varibles:
    
    x = [R1(k);C1(k);R2(k);C2(k);Rt(k)];
    model_rmse(x,current_int, voltage_int, time_int,ocv_int,Ts);
    Cfunction = @(x) model_rmse(x,current_int, voltage_int, time_int,ocv_int,Ts);
    %% PSO
    problem.CostFunction = Cfunction; % Costfunction only depends on Parameters
    problem.nVar = 5;%Number of ECM parameters
    problem.VarMin =[1e-5,0.1,1e-5,0.1,1e-5];
    problem.VarMax = [1,100,1,tau_max,1];


    % Constriction Coefficients
    kappa = 1;
    phi1 = 2.05;
    phi2 = 2.05;
    phi = phi1 + phi2;
    chi = 2*kappa/abs(2-phi-sqrt(phi^2-4*phi));

    % PSO Parameters
    params.MaxIt = 75;        % Maximum Number of Iterations
    params.nPop = 20;           % Population Size (Swarm Size)
    params.w = chi;             % Intertia Coefficient
    params.wdamp = 0.99;           % Damping Ratio of Inertia Coefficient
    params.c1 = chi*phi1;       % Personal Acceleration Coefficient
    params.c2 = chi*phi2;       % Social Acceleration Coefficient
    params.ShowIterInfo = true; % Flag for Showing Iteration Informat

    % PSO Function
    out = PSO(problem,params);
    %% Showing Results
    x = out.BestSol.Position;
    disp("LS RMSE="+num2str(RMSError)+"\nPSO RMSE ="+ num2str(out.BestSol.Cost));
    R1(k)=x(1);C1(k)=x(2)/R1(k);R2(k)=x(3);C2(k)=x(4)/R2(k);Rt(k)=x(5);
    tau1(k)=x(2); tau2(k)=x(4);
    [Vsim, simulation_time] = TH2RC_sim(R1(k),tau1(k),R2(k),tau2(k),Rt(k),ocv_int,current_int,time_int,Ts);
    figure();
    subplot(2,1,1)
    plot(time_int,voltage_int,simulation_time, Vsim,"--",time_int,Vt,":");
    legend(["Vmeas","V_PSO","V_LS"]);
    subplot(2,1,2)
    plot(time_int,Vsim-voltage_int,"--",time_int,Vt-voltage_int,":");
    %ylim([-0.1 0.2])
    legend(["V_PSO","V_LS"]);
    toc
    %% Saving CSV Data
    if(k==3)
        table_data=array2table([downsample(simulation_time,10) downsample(voltage_int,10) downsample(Vsim,10) downsample(Vt,10)] ); % X vs Y table
        table_data.Properties.VariableNames = ["Time","Vmeas","VPSO","VLS"]; %
        writetable(table_data,BatteryType+"_2RC_PSO_Parameter.csv");
    end
end


%% Flip Parameter for Simulink look-up table.
SOC_LUT = flip(SOC_LUT);

OCV= flip(OCV);
if(BatteryType=="NMC")
    SOC_INTP=0:1/66:1;
    OCV_INTP=interp1(SOC_LUT,OCV,SOC_INTP,"linear",'extrap');
    OCV=OCV_INTP;
end
R1=flip(R1);
C1=flip(C1);
R2=flip(R2);
C2=flip(C2);
Rt=flip(Rt);
save(BatteryType+"_2RC_Parameters_PSO_"+datestr(now,"dd_mm_yyyy_HH_MM")+".mat","R1","C1","R2","C2","Rt","OCV","SOC_LUT");

