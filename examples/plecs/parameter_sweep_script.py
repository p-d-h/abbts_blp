# C:\Users\PascalHelfenstein\Documents\Plexim\PLECS 4.7 (64 bit)\demos\buck_converter_with_parameter_sweep

import xmlrpc.client
import jsonrpc_requests		# for JSON-RPC
import os


HOST_ADDRESS	= "http://localhost:1080/RPC2"
MODEL_NAME  = "buck_converter_with_parameter_sweep"		
METHOD			= "XML"				# "XML", "JSON"

# import RPC module
if METHOD == "JSON":
    server = jsonrpc_requests.Server(HOST_ADDRESS)

elif METHOD == "XML":
    server = xmlrpc.client.Server(HOST_ADDRESS)

L_values = [40, 60, 80, 100, 120, 140, 160, 180, 200, 220]

start_time = 0.001
end_time = 0.002
number_of_steps = 500
output_times_vec = [start_time + x*(end_time-start_time)/number_of_steps for x in range(number_of_steps)]

simStructs = []

for varL in L_values:
    simStructs.append({"ModelVars": {"varL": varL * 1e-6},
                       "Name" : f"L = {varL}μH",
                       "SolverOpts": {"OutputTimes": output_times_vec}})

# simStructs[4]["ModelVars"]["varR"] = 0

callback = """
if ischar(result)
    disp(["There is a simulation error for the fifth case (" name ") where varR = 0 is artificially set to zero. Nevertheless the results for the other cases are still calculated"]);
else
    plecs('scope', './Scope', 'HoldTrace', name);
    
    [maxi, maxidx] = max(result.Values(1,:));
    maxt = result.Time(maxidx);
    result = [maxi, maxt];
end
"""

server.plecs.load(os.path.join(os.getcwd(), MODEL_NAME))
server.plecs.scope(MODEL_NAME + "/Scope", "ClearTraces")
results = server.plecs.simulate(MODEL_NAME, simStructs, callback)
server.plecs.close(MODEL_NAME)

for i, varL in enumerate(L_values):
    if isinstance(results[i], list):
        print(f"Max current for L={varL}uH: {results[i][0]:.6f}A at {results[i][1]:.6f}s")
    else:
        print(f"There is a simulation error for case 5 (L={varL}uH) where varR is artificially set to zero. Nevertheless the results for the other cases are still calculated.\n")
        print(f"{results[i]}")
