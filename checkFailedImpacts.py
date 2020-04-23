import os
import ROOT as r 

toResubmit=[]
for fil in os.listdir('.'):
    if '.root' not in fil: continue
    if 'higgsCombine_paramFit_data_' not in fil: continue
    tf = r.TFile.Open(fil)
    limit = tf.Get('limit')
    nuisName = fil.replace('higgsCombine_paramFit_data_','').replace('.MultiDimFit.mH125.root','')
    if not limit:
        toResubmit.append(nuisName)
        continue
    if limit.GetEntries() < 3: 
        toResubmit.append(nuisName)
        continue
    if limit.GetEntries() > 3:
        print kk
    vals = [ ]
    for fit in limit:
        vals.append( getattr(fit, nuisName) ) 
    up = max(vals)
    dn = min(vals)
    vals.remove(up); vals.remove(dn)
    nom = vals[0]
    if abs(nom-up) < 1e-3 or abs(nom-dn) < 1e-3:
        toResubmit.append(nuisName)
print ' '.join(toResubmit)
print len(toResubmit)
