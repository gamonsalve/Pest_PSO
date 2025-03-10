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
RMSE_iter=zeros(75,10);
phies=linspace(2.1,4.1,10);
plotting=true; 
initial_points=[];
for k=1:20
    initial_points(k,:)=unifrnd([1e-5,0.1,1e-5,0.1,1e-5], [1,100,1,tau_max,1], [1 5]);
end
for p=1:length(phies)
    k=3;
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
    
    %% Particle Swarm Optimization
    % complete system simulation using the previously found varibles:
    
    x = [R1(k);C1(k);R2(k);C2(k);Rt(k)];
    %model_rmse(x,current_int, voltage_int, time_int,ocv_int,Ts);
    Cfunction = @(x) model_rmse(x,current_int, voltage_int, time_int,ocv_int,Ts);
    %% PSO
    problem.CostFunction = Cfunction; % Costfunction only depends on Parameters
    problem.nVar = 5;%Number of ECM parameters
    problem.VarMin = [1e-5,0.1,1e-5,0.1,1e-5];
    problem.VarMax = [1,100,1,tau_max,1];


    % Constriction Coefficients
    kappa = 1;
    phi1 = phies(p)/2;
    phi2 = phies(p)/2;
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
    out = PSO_phi_validation(problem,params,initial_points);
    RMSE_iter(:,p)=out.BestCosts;
    %% Showing Results
    x = out.BestSol.Position;
    R1(k)=x(1);C1(k)=x(2)/R1(k);R2(k)=x(3);C2(k)=x(4)/R2(k);Rt(k)=x(5);
    tau1(k)=x(2); tau2(k)=x(4);
    [Vsim, simulation_time] = TH2RC_sim(R1(k),tau1(k),R2(k),tau2(k),Rt(k),ocv_int,current_int,time_int,Ts);
    if (plotting)
    figure();
        subplot(2,1,1)
        plot(time_int,voltage_int,simulation_time, Vsim,"--");
        legend(["Vmeas","V_PSO"]);
        subplot(2,1,2)
        plot(time_int,Vsim-voltage_int,"--");
        %ylim([-0.1 0.2])
        legend(["V_PSO"]);
    end
    toc
    %% Saving CSV Data
end
%% Ploting RSME vs Iterations

iter=[1:params.MaxIt];
figure();
for k=1:10
    plot(iter,RMSE_iter(:,k));
    hold on;
end
legend(string(phies));
hold off


%
% Copyright (c) 2016, Yarpiz (www.yarpiz.com)
% All rights reserved. Please read the "license.txt" for license terms.
%
% Project Code: YTEA101
% Project Title: Particle Swarm Optimization Video Tutorial
% Publisher: Yarpiz (www.yarpiz.com)
% 
% Developer and Instructor: S. Mostapha Kalami Heris (Member of Yarpiz Team)
% 
% Contact Info: sm.kalami@gmail.com, info@yarpiz.com
%

function out = PSO_phi_validation(problem, params,initial_points)

    %% Problem Definiton

    CostFunction = problem.CostFunction;  % Cost Function

    nVar = problem.nVar;        % Number of Unknown (Decision) Variables

    VarSize = [1 nVar];         % Matrix Size of Decision Variables

    VarMin = problem.VarMin;	% Lower Bound of Decision Variables
    VarMax = problem.VarMax;    % Upper Bound of Decision Variables


    %% Parameters of PSO

    MaxIt = params.MaxIt;   % Maximum Number of Iterations

    nPop = params.nPop;     % Population Size (Swarm Size)

    w = params.w;           % Intertia Coefficient
    wdamp = params.wdamp;   % Damping Ratio of Inertia Coefficient
    c1 = params.c1;         % Personal Acceleration Coefficient
    c2 = params.c2;         % Social Acceleration Coefficient

    % The Flag for Showing Iteration Information
    ShowIterInfo = params.ShowIterInfo;    

    MaxVelocity = 0.2*(VarMax-VarMin);
    MinVelocity = -MaxVelocity;
    
    %% Initialization

    % The Particle Template
    empty_particle.Position = [];
    empty_particle.Velocity = [];
    empty_particle.Cost = [];
    empty_particle.Best.Position = [];
    empty_particle.Best.Cost = [];

    % Create Population Array
    particle = repmat(empty_particle, nPop, 1);

    % Initialize Global Best
    GlobalBest.Cost = inf;

    % Initialize Population Members
    for i=1:nPop

        % Generate Random Solution
        particle(i).Position = initial_points(i,:);

        % Initialize Velocity
        particle(i).Velocity = zeros(VarSize);

        % Evaluation
        particle(i).Cost = CostFunction(particle(i).Position);

        % Update the Personal Best
        particle(i).Best.Position = particle(i).Position;
        particle(i).Best.Cost = particle(i).Cost;

        % Update Global Best
        if particle(i).Best.Cost < GlobalBest.Cost
            GlobalBest = particle(i).Best;
        end

    end

    % Array to Hold Best Cost Value on Each Iteration
    BestCosts = zeros(MaxIt, 1);


    %% Main Loop of PSO

    for it=1:MaxIt

        for i=1:nPop

            % Update Velocity
            particle(i).Velocity = w*particle(i).Velocity ...
                + c1*rand(VarSize).*(particle(i).Best.Position - particle(i).Position) ...
                + c2*rand(VarSize).*(GlobalBest.Position - particle(i).Position);

            % Apply Velocity Limits
            particle(i).Velocity = max(particle(i).Velocity, MinVelocity);
            particle(i).Velocity = min(particle(i).Velocity, MaxVelocity);
            
            % Update Position
            particle(i).Position = particle(i).Position + particle(i).Velocity;
            
            % Apply Lower and Upper Bound Limits
            particle(i).Position = max(particle(i).Position, VarMin);
            particle(i).Position = min(particle(i).Position, VarMax);

            % Evaluation
            particle(i).Cost = CostFunction(particle(i).Position);

            % Update Personal Best
            if particle(i).Cost < particle(i).Best.Cost

                particle(i).Best.Position = particle(i).Position;
                particle(i).Best.Cost = particle(i).Cost;

                % Update Global Best
                if particle(i).Best.Cost < GlobalBest.Cost
                    GlobalBest = particle(i).Best;
                end            

            end

        end

        % Store the Best Cost Value
        BestCosts(it) = GlobalBest.Cost;

        % Display Iteration Information
        if ShowIterInfo
            disp(['Iteration ' num2str(it) ': Best Cost = ' num2str(BestCosts(it))]);
        end

        % Damping Inertia Coefficient
        w = w * wdamp;

    end
    
    out.pop = particle;
    out.BestSol = GlobalBest;
    out.BestCosts = BestCosts;
    out.particle=particle;
    
end
