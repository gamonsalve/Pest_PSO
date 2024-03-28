%This script load all the data needed to simulate the model
%RC_Model_Custom_KF_vout. 
%% Load Dataset
clc; clear variables;
[file,folder]=uigetfile('*.*','Select Data File');
path=fullfile(folder,file);
load(path);
if(exist("Robot","var")==1)
    Battery=Robot;
end
[time, Ia, Ic] = unique(Battery.Time); % Delete duplicate time
voltage = Battery.Voltage(Ia);
current = Battery.Current(Ia); % Discharge current must be positive
SOC_REAL = 1+Battery.Ah(Ia)/Battery.Capacity; % Discharge current must be positive
Ah=Battery.Ah;
initialPoint=1;
%% Load Parameters
[file,folder]=uigetfile('*.*','Select Parameter File');
path=fullfile(folder,file);
load(path);

%% save Vocv vs SoC .csv Data
VocvTable=array2table([downsample(SOC_EST',1) downsample(Vocv',1)]); %Vocv vs SoC Table
VocvTable.Properties.VariableNames(1:2) = {'SOC','Vocv'}; %Vocv vs SoC Table Headers
[file,folder]=uiputfile("*.csv","Save Vocv vs SoC .csv data file");
savePath=fullfile(folder,file);
writetable(VocvTable,savePath)

%% Run simulation and Proccess Data
simulation=sim("Est_UKF2RC_OCV");


Vmeasured=simulation.logsout.getElement("Voltage Measured").Values;
Vmodeled=simulation.logsout.getElement("Voltage Modeled").Values;
Vestimated=simulation.logsout.getElement("Voltage Estimated").Values;
Verror=simulation.logsout.getElement("Voltage Error").Values;
SOCestimated=simulation.logsout.getElement("SoC Estimated").Values;
SOCmeasured=simulation.logsout.getElement("SoC Measured").Values;
SOCError=simulation.logsout.getElement("SoC Error").Values;

figure(1)
subplot(2,1,1)
plot(Vmeasured);
hold on
plot(Vmodeled);
plot(Vestimated);
legend(["Measured","Simulation","Vmodeled"]);
subplot(2,1,2)
plot(Verror);

figure(2)
subplot(2,1,1)
plot(SOCestimated);
hold on;
plot(SOCmeasured);
plot(SOCUpper);
plot(SOCLower);
legend(["Measured","Simulation","Upper Limit","Lower Limit"]);
subplot(2,1,2)
plot(SOCError)

%% Save CSV Files
VmeasuredTable = array2table([downsample(Vmeasured.Time,10) downsample(Vmeasured.Data,10)]);
VmodeledTable = array2table([downsample(Vmodeled.Time,10) downsample(Vmodeled.Data,10)]);
VestimatedTable = array2table([downsample(Vestimated.Time,10) downsample(Vestimated.Data,10)]);
VerrorTable = array2table([downsample(Verror.Time,10) downsample(Verror.Data,10)]);
SOCestimatedTable = array2table([downsample(SOCestimated.Time,10) downsample(SOCestimated.Data,10)]);
% Filter Limits
SOCUpperTable = array2table([downsample(SOCUpper.Time,10) downsample(reshape(SOCUpper.Data,[length(SOCUpper.Time),1]),10)]); %Reshaped Data
SOCLowerTable = array2table([downsample(SOCLower.Time,10) downsample(reshape(SOCLower.Data,[length(SOCUpper.Time),1]),10)]); %Reshaped Data
SOCmeasuredTable = array2table([downsample(SOCmeasured.Time,10) downsample(SOCmeasured.Data,10)]);
SOCErrorTable = array2table([downsample(SOCError.Time,10) downsample(SOCError.Data,10)]);


VmeasuredTable.Properties.VariableNames(1:2) = {'Time','Data'}; %VmeasuredTable Table Headers
VmodeledTable.Properties.VariableNames(1:2) = {'Time','Data'}; %VmodeledTable Table Headers
VestimatedTable.Properties.VariableNames(1:2) = {'Time','Data'}; %VestimatedTable Table Headers
VerrorTable.Properties.VariableNames(1:2) = {'Time','Data'}; %VerrorTable Table Headers
SOCestimatedTable.Properties.VariableNames(1:2) = {'Time','Data'}; %SOCestimatedTable Table Headers
SOCmeasuredTable.Properties.VariableNames(1:2) = {'Time','Data'}; %SOCmeasuredTable Table Headers
SOCErrorTable.Properties.VariableNames(1:2) = {'Time','Data'}; %SOCErrorTable Table Headers

dirName=uigetdir("Select the folder where data will be stored");
fileNames=["Vmeasured.csv","Vmodeled.csv","Vestimated.csv","Verror.csv","SOCestimated.csv","SOCmeasured.csv","SOCError.csv"];
tables={VmeasuredTable VmodeledTable VestimatedTable VerrorTable SOCestimatedTable SOCmeasuredTable SOCErrorTable};

for i=1:length(fileNames)
    savePath=fullfile(dirName,fileNames(i));
    writetable(tables{1,i},savePath)
end

