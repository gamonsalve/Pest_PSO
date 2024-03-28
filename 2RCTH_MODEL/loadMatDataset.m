function Battery = loadMatDataset(filename)
%LOADMATDATASET Summary of this function goes here
%   Detailed explanation goes here
%% Get pulse information
% [fileName, filePath] = uigetfile('*', 'Select the Charging test file', '.');
% load(fullfile(filePath,fileName));
% load("SLA_Characterization_test.mat");
load(filename);
if(exist("Robot","var") == 1)
    Battery=Robot;
elseif (exist("meas","var") ==1)
    Battery=meas;
    Battery.Capacity = 2.9;
end
% Remove duplicate time
[time, Ia, Ic] = unique(Battery.Time); % Delete duplicate time
Battery.Time = time;
Battery.Voltage = Battery.Voltage(Ia);
Battery.Current = Battery.Current(Ia); % Discharge current must be negative in RC Model
Battery.Ah = Battery.Ah(Ia);

end

