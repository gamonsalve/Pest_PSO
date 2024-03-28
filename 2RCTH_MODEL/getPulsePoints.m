function [Relaxation,Stress] = getPulsePoints(current,time)
% GETPULSEPOINTS get the Relaxation and Pulse points.
%   Detailed explanation goes here
% This function takes the current and time vector of a
% battery characterization test and performs an analysis to stract the
% critical points, that is the point when the relaxation period starts and
% ends. 
PulseFinished = false;
Stress=[];
Relaxation=[]; 

%Extract Pulse Information
for t=2:length(time)
    if(current(t)~=0 && current(t-1)==0)
        if (PulseFinished)
            % Get last relaxation point
            Rend=t-1;
            % let's save the critical points
            Stress=[Stress;Pstart,Pend];
            Relaxation=[Relaxation;Rstart,Rend];
            PulseFinished=false;
        end
        % Pulse starts at t, Relax ends t-1
        Pstart=t;
        
    elseif(current(t-1)~=0 && current(t)==0)
        % pulse ends at t-1, Relax starts at t
        Pend=t-1;
        Rstart=t;
        PulseFinished=true;
    end
    
    
end
% process last pulse
if(PulseFinished)
    %This is the last pulse, relaxation will end at the end of the test.
    % let's save the last pulse points
    Stress=[Stress;Pstart,Pend];
    Relaxation=[Relaxation;Rstart,length(time)];
    PulseFinished=false;
end
%Instant before the beginning of first pulse.
Relaxation=[1,Stress(1,1)-1;Relaxation]; 
end

