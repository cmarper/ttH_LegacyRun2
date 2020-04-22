import ROOT as r 
import CombineHarvester.CombineTools.ch as ch
import os

for card in os.listdir('.'):
    if '.txt' not in card: continue
    cb = ch.CombineHarvester() 
    theChan=None
    theYear=None
    for chan in ['ttH_2lss_0tau','ttH_2lss_1tau','ttH_3l_0tau','ttH_4l','ttH_cr_3l','ttH_cr_4l']:
        if card.startswith(chan): theChan=chan
    #for year in ['2016','2017','2018']:
    for year in ['2018']:
        if year in card: theYear=year
    if not theChan:
        print card, theChan
        raise RuntimeError()
    print card, chan
    cb.ParseDatacard( card, "$CHANNEL.txt" )
    #cb.ForEachProc( lambda p : cb.cp().process([p.process()]).RenameSystematic( cb,  'CMS_ttHl_pileup', 'CMS_ttHl_pileup_%s_%s'%(theChan,theYear)))
    cb.ForEachProc( lambda p : cb.cp().process([p.process()]).RenameSystematic( cb,  'CMS_res_j_endcap1_2018', 'CMS_res_j_endcap1_%s_%s'%(theChan,theYear)))
    writer = ch.CardWriter('new_split/%s'%card, 'new_split/%s.root'%(card.replace('.txt','')))
    writer.WriteCards('.',cb)
    
#out = r.TFile.Open('combined.root')
#cmb.WriteDataCard('combined.kk',out)
