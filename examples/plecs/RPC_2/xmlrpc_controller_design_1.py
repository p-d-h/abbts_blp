# import modules and functions from provided library
from tutorial_functions_library import *

import xmlrpc.client

import jsonrpc_requests		# for JSON-RPC
import base64				# deserialise MAT-file contents for JSON-RPC

HOST_ADDRESS	= "http://localhost:1080/RPC2"
MODEL_NAME		= "xmlrpc_controller_design"
OUTPUT_FORMAT	= "MatFile"			
METHOD			= "XML"				# "XML", "JSON"

# import RPC module
if METHOD == "JSON":
	server = jsonrpc_requests.Server(HOST_ADDRESS)

elif METHOD == "XML":
	server = xmlrpc.client.Server(HOST_ADDRESS)
    
# import user-defined parameter definitions
Param = SystemParameters()
# define transfer function variable 's'
s = ct.tf('s')
# define transfer functions for equivalent delays and plant
Delays_TF = 1/(1+s*Param['Tei'])
Plant_TF = Param['Krl']/(1+s*Param['Trl'])
# calculate transfer functions
TFs = LoopTFsCalculation_PIgains(Param['Ki'],Param['Ti'],Plant_TF,Delays_TF)
# develop 1st-order approximations of transfer functions
Param['Tet']=2*Param['Tei']
TFs['Hci'].append(1/(1+s*Param['Tet']))
# Plot frequency response comparison for both control designs
FigNameFreq1 = 'Fig: Frequency response of closed-loop current control transfer functions'
LegendFreq1 = ['Hci Optimum tracking','Hci Improved rejection','Hci 1st order approx.']
PlotFreqResponses(TFs['Hci'],FigNameFreq1,LegendFreq1)
FigNameFreq2 = 'Fig: Frequency response of disturbance rejection transfer functions'
LegendFreq2 = ['Hdi Optimum tracking','Hdi Improved rejection']
PlotFreqResponses(TFs['Hdi'],FigNameFreq2,LegendFreq2)
# Plot current tracking step response for both control designs
TitleStep1 = 'Fig: Step response of closed-loop current control transfer functions'
LegendStep1 = ['Hci Optimum tracking','Hci Improved rejection','Hci 1st order approx.']
XYLabels1 = ['time (s)','Inductor Current (A)']
StepData_Hci = PlotStepResponses(TFs['Hci'],TitleStep1,LegendStep1,XYLabels1,[Param['t_stepRef'],Param['Istep']])
TitleStep2 = 'Fig: Step response of disturbance rejection transfer functions'
LegendStep2 = ['Hdi Optimum tracking','Hdi Improved rejection']
XYLabels2 = ['time (s)','Inductor Current (A)']
StepData_Hdi = PlotStepResponses(TFs['Hdi'],TitleStep2,LegendStep2,XYLabels2,[0,1])