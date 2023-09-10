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
# Load PLECS model
full_path = os.path.abspath(os.getcwd())
file_name = 'xmlrpc_controller_design'
server.plecs.load(full_path+'/'+file_name)
# Define simulation parameters
opts = LoadSimParameters(Param)
# Define variables for signal and time data
Time = []
Ic_d_ref_sim = []
Ic_d_sim = []
# Run simulations with two different optStructs
opts['ModelVars']['Ti'] = Param['Ti'][0]
opts['OutputFormat'] = OUTPUT_FORMAT

if METHOD == "JSON":
    Data_raw = server.plecs.simulate(MODEL_NAME, opts)
    Data_sim1 = sio.loadmat(io.BytesIO(base64.b64decode(Data_raw)))

elif METHOD == "XML":
    Data_raw = server.plecs.simulate(MODEL_NAME, opts)
    Data_sim1 = sio.loadmat(io.BytesIO(Data_raw.data))

#Data_raw = server.plecs.simulate(file_name, opts).data
#Data_sim1 = sio.loadmat(io.BytesIO(base64.b64decode(Data_raw)))

Time.append( Data_sim1['Time'][0] )
Ic_d_ref_sim.append( Data_sim1['Values'][0] )
Ic_d_sim.append( Data_sim1['Values'][1] )
opts['ModelVars']['Ti'] = Param['Ti'][1]

if METHOD == "JSON":
    Data_raw = server.plecs.simulate(MODEL_NAME, opts)
    Data_sim2 = sio.loadmat(io.BytesIO(base64.b64decode(Data_raw)))

elif METHOD == "XML":
    Data_raw = server.plecs.simulate(MODEL_NAME, opts)
    Data_sim2 = sio.loadmat(io.BytesIO(Data_raw.data))

#Data_raw = server.plecs.simulate(file_name, opts).data
#Data_sim2 = sio.loadmat(io.BytesIO(base64.b64decode(Data_raw)))

Time.append( Data_sim2['Time'][0] )
Ic_d_ref_sim.append( Data_sim2['Values'][0] )
Ic_d_sim.append( Data_sim2['Values'][1] )
# Close the model
server.plecs.close(file_name)
# Plot theoretical and simulated step responses for both control designs
Plot_XY_Pairs = [[Time[0],Ic_d_ref_sim[0]],[Time[0],Ic_d_sim[0]],StepData_Hci[0]]
TitleResults = 'Fig: Theoretical responses Vs Simulated model, PI reg. 1'
LegendResults = ['Reference','Simulated','Theoretical']
LabelResults = ['time (s)','Id (A)']
plt1 = PlotSimResults(Plot_XY_Pairs,TitleResults,LegendResults,LabelResults,Param)
Plot_XY_Pairs = [[Time[1],Ic_d_ref_sim[1]],[Time[1],Ic_d_sim[1]],StepData_Hci[1]]
TitleResults = 'Fig: Theoretical responses Vs Simulated model, PI reg. 2'
LegendResults = ['Reference','Simulated','Theoretical']
LabelResults = ['time (s)','Id (A)']
plt2 = PlotSimResults(Plot_XY_Pairs,TitleResults,LegendResults,LabelResults,Param)
plt2.show()