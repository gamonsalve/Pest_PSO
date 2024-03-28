function [rmserror] = model_rmse(x, current,voltage,time,ocv_int,Ts)
%MODEL_RMSE Summary of this function goes here
%   Detailed explanation goes here
R1=x(1);tau1=x(2);R2=x(3);tau2=x(4);Rt=x(5);
[Vsim,t] = TH2RC_sim(R1,tau1,R2,tau2,Rt,ocv_int,current,time,Ts);
rmserror=rmse(Vsim,voltage);
% figure()
% plot(time,Vsim,time,voltage,"--");
end

