function [PulseData] = ProcessPulse(Battery, pulse_start,indexes,Relax,Stress)
%PROCESSPULSE Summary of this function goes here
%   Detailed explanation goes here
PulseData.Relax = Relax;
PulseData.Stress = Stress;
PulseData.Voltage = Battery.Voltage(indexes);
PulseData.Current = Battery.Current(indexes);
PulseData.Time = Battery.Time(indexes)-Battery.Time(pulse_start);
PulseData.SoC = (Battery.Capacity+Battery.Ah(indexes))/Battery.Capacity;
end

