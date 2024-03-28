function [Data] = loadTable()
%loadTable Creates a .mat file from .xlsx or .csv File
%   The .mat file contains a variable with information about
%   current, votlage, ax, ay, az, speedR and speedL
%   The variable Name is Robot
%% Load Data from excel File
clc; clear variables;
[file,folder]=uigetfile('*.*','Select Data File');
path=fullfile(folder,file);
tabledata = readtable(path);
%% Get the Different Vectors (Voltage, Current, ax, ay, az, speed L and speed R)
voltage=tabledata.value(tabledata.field=="voltage",:);
current=tabledata.value(tabledata.field=="current",:);
ax=tabledata.value(tabledata.field=="ax",:);
ay=tabledata.value(tabledata.field=="ay",:);
az=tabledata.value(tabledata.field=="az",:);
speedL=tabledata.value(tabledata.field=="speedL",:);
speedR=tabledata.value(tabledata.field=="speedR",:);
currentTime=string(tabledata.time(tabledata.field=="current",:));
voltageTime=string(tabledata.time(tabledata.field=="voltage",:));

% Convert cell to double
if (iscell(voltage))
    voltage=cellfun(@str2double,voltage);
    current=cellfun(@str2double,current);
    ax=cellfun(@str2double,ax);
    ay=cellfun(@str2double,ay);
    az=cellfun(@str2double,az);
    speedL=cellfun(@str2double,speedL);
    speedR=cellfun(@str2double,speedR);
end
%% Get current TimeStamp
stringTime=currentTime;
try
    currentTime=datetime(stringTime,"Format",'yyyy-MM-dd''T''HH:mm:ss''Z');
    wrongIndex=isnat(currentTime);
    currentTime(wrongIndex)=datetime(stringTime((wrongIndex)),"Format",'yyyy-MM-dd''T''HH:mm:ss.S''Z');
    ctimeStamp=posixtime(currentTime);
catch
    currentTime=datetime(stringTime,"Format",'yyyy-MM-dd''T''HH:mm:ss.S''Z');
    wrongIndex=isnat(currentTime);
    currentTime(wrongIndex)=datetime(stringTime((wrongIndex)),"Format",'yyyy-MM-dd''T''HH:mm:ss''Z');
    ctimeStamp=posixtime(currentTime);
end

%Get voltage TimeStamp
stringTime=voltageTime;
try
    voltageTime=datetime(stringTime,"Format",'yyyy-MM-dd''T''HH:mm:ss''Z');
    wrongIndex=isnat(voltageTime);
    voltageTime(wrongIndex)=datetime(stringTime(wrongIndex),"Format",'yyyy-MM-dd''T''HH:mm:ss.S''Z');
    vtimeStamp=posixtime(voltageTime);
catch
    voltageTime=datetime(stringTime,"Format",'yyyy-MM-dd''T''HH:mm:ss.S''Z');
    wrongIndex=isnat(voltageTime);
    voltageTime(wrongIndex)=datetime(stringTime(wrongIndex),"Format",'yyyy-MM-dd''T''HH:mm:ss''Z');
    vtimeStamp=posixtime(voltageTime);
end
% Check that timestamps are equal
check=vtimeStamp-ctimeStamp;

if(isempty(check(check~=0)))
    disp("The time vector are identical")
    
end

%% Create variables
Robot.Timestamp=vtimeStamp; %Absolute time
%time=vtimeStamp-vtimeStamp(1); %Set 0 as the test start time
time=(0:1:length(voltage)-1)'*0.1; %Since we measured data every 0.1s we created a vector with Ts=0.1s
Robot.Time=time; %Test time
Robot.Voltage=voltage;
currentValue=current;
Robot.Current=(currentValue);
Robot.Current=(Robot.Current-2.5018)/(24.5e-3); %Voltage @ 0A=2,502327, facteur correction: 1.022107813
Robot.Current(abs(Robot.Current)<1e-1)=0;
Robot.Capacity=input("Battery Capacity in Ah: ");
Robot.Ah=cumtrapz(time,Robot.Current/3600);
Robot.ax= ax;
Robot.ay= ay;
Robot.az= az;
Robot.speedL=speedL;
Robot.speedR=speedL;

%% Save data to workspace
[file,folder]=uiputfile("robot_data.mat","Select where to save the .mat File");
savePath=fullfile(folder,file);
save(savePath,"Robot");

%% Return Proccesed Data
Data=Robot;
end

