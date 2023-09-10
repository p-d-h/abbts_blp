import control as ct
import matplotlib.pyplot as plt
import os
import scipy.io as sio
import io


def SystemParameters():
    #Electrical parameters
    Param = {'R' : 0.5}
    Param['L'] = 3e-3
    Param['fc'] = 20e3
    Param['Ts'] =  1/Param['fc']
    Param['Tei'] = 1.5*Param['Ts']
    Param['Trl'] = Param['L']/Param['R'] # Load time constant 
    Param['Ti'] = [Param['Trl'],10*Param['Tei']]  # [0]=For Zero-pole concellation, [1]= Better disturbance rejection
    Param['Krl'] = 1/Param['R'] # Load TF DC gain Krl/(1+sTrl) = (1/R)/(1+s(L/R))
    Param['Kpwm'] = 1
    Param['D'] = 2**(1/2)/2 # value chosen for technical optimun
    Param['Ki'] = Param['Trl']/(4*Param['D']**2*Param['Tei']*Param['Kpwm']*Param['Krl']) # same as eq(22) but including D^2 as variable
    #Current step definition
    Param['Istep'] = 10 
    Param['t_switching'] = 0.03
    Param['t_stepRef'] = Param['t_switching']+0.2
    Param['t_end'] = Param['t_stepRef']+0.5
    return Param

def LoopTFsCalculation_PIgains(K,T,Plant,Delays):
    s=ct.tf('s')
    PI_reg = []
    Hci = []
    Hoi = []
    Hdi = []
    L_Ti=len(T)
    for i in range(L_Ti):
        PI_reg.append( K*(1+s*T[i])/(s*T[i]) )
        Hoi.append( PI_reg[i]*Delays*Plant ) # Open loop TF
        Hci.append( Hoi[i]/(1+Hoi[i]) ) # Close loop TF
        Hdi.append( Plant / (1+Hoi[i]) ) # Disturbance rejection TF
    TFs = {'PI' : PI_reg}
    TFs['Hoi'] = Hoi
    TFs['Hci'] = Hci
    TFs['Hdi'] = Hdi
    TFs['Plant'] = Plant
    TFs['Delays'] = Delays
    
    return TFs

def PlotFreqResponses(TF,Title,Legend):
    L_TF = len(TF)
    plt.figure()
    for i in range(L_TF):
        ct.bode(TF[i],label=Legend[i],dB=True,Hz=True,deg=True)
    plt.legend();
    return

def PlotStepResponses(TF,Title,Legend,Labels,Param):
    L_TF=len(TF)
    step_t=[None]*L_TF
    step_values=[None]*L_TF
    plt.figure(Title)
    for i in range(L_TF):
        step_t[i],step_values[i] = ct.step_response(TF[i]);
        plt.plot(step_t[i]+Param[0],step_values[i]*Param[1])
    plt.xlabel(Labels[0])
    plt.ylabel(Labels[1])
    plt.grid()
    plt.legend(Legend,loc='lower right');
    StepDataList=[[[],[]],[[],[]]]
    for x in step_t[0]:
        StepDataList[0][0].append(x.tolist()+Param[0])
    for x in step_t[1]:
        StepDataList[1][0].append(x.tolist()+Param[0])
    for x in step_values[0]:
        StepDataList[0][1].append(x.tolist()*Param[1])
    for x in step_values[1]:
        StepDataList[1][1].append(x.tolist()*Param[1])
    
    return StepDataList

def LoadSimParameters(Param):
    opts = {'ModelVars' : { 'fc' : Param['fc']}}
    opts['ModelVars']['R'] =  Param['R']
    opts['ModelVars']['L'] =  Param['L']
    #Initialize control gains
    opts['ModelVars']['Ki'] = Param['Ki']
    opts['ModelVars']['Ti'] = Param['Ti'][0]
    #Timing step functions
    opts['ModelVars']['Istep'] = Param['Istep']
    opts['ModelVars']['t_switching'] = Param['t_switching']
    opts['ModelVars']['t_stepRef'] = Param['t_stepRef']
    opts['ModelVars']['t_end'] = Param['t_end']
    return opts


def PlotSimResults(Vars,Title,Legend,Labels,Param):

    # Data visualization
    plt.figure(Title)
    plt.xlabel(Labels[0])
    plt.ylabel(Labels[1])
    plt.grid()
    #
    plt.plot(Vars[0][0], Vars[0][1])
    plt.plot(Vars[1][0], Vars[1][1])
    plt.plot(Vars[2][0], Vars[2][1])
    plt.xlim(Param['t_stepRef']-0.001,Param['t_stepRef']+0.005)
    #
    plt.legend(Legend,loc='lower right');
    return plt