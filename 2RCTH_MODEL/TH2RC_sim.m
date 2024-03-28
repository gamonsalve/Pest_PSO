function [Vt,t] = TH2RC_sim(R1,tau1,R2,tau2,Rt,ocv_int,current,time,Ts)
%2RCTHSIM Summary of this function goes here
%   Detailed explanation goes here
C1=tau1/R1;
C2=tau2/R2;
RCfact = [exp(-Ts/(R1*C1));exp(-Ts/(R2*C2))];
A = diag(RCfact);
B = (1-RCfact).*[R1;R2];
C = [-1 -1]; % voltage are negative: RCv=-V1-V2 then Vt=Vocv-V1-V2-Rt*I=Vocv+Rcv-I*Rt
D = 0;
RCModel = ss(A,B,C,D,Ts);
[RCv,t]=lsim(RCModel,current,time,[0 0]);
Vt=ocv_int+RCv-Rt*current;
end

