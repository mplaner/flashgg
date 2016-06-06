# Imports
import cx_Oracle
import socket
import sys
# For the parsing
import re


class DBQueryTool:

    def __init__(self) :
        # Connect to the Database
        hostname = socket.gethostname()
        if hostname.find('lxplus') > -1: self.dsn_ = 'cms_omds_adg' #offline
        else: self.dsn_ = 'cms_omds_lb' #online

        orcl = cx_Oracle.connect(user='cms_hlt_r',password='convertMe!',dsn=self.dsn_)
        orcl = cx_Oracle.connect(user='cms_trg_r',password='X3lmdvu4',dsn=self.dsn_)
        # Create a DB cursor
        self.curs = orcl.cursor()
        self.lumicurs=orcl.cursor()
    def test_query(self):
        # [run number] [first lumi] [last lumi] --automatically skips LS which fail DCS json
        print "run number: ",sys.argv[2]," from LS ",sys.argv[3]," to LS ",sys.argv[4]
        
        bunches=25
        query = "SELECT LHCFILL FROM CMS_WBM.RUNSUMMARY WHERE RUNNUMBER=%s" % (sys.argv[2])
        self.curs.execute(query)
        fill = self.curs.fetchone()[0]
        # Get the number of colliding bunches
        query = "SELECT NCOLLIDINGBUNCHES FROM CMS_RUNTIME_LOGGER.RUNTIME_SUMMARY WHERE LHCFILL=%s" % (fill)
        self.curs.execute(query)
        temp =  self.curs.fetchall()[0]
        bunches= int(temp[0])
        
        lumiquery="""SELECT SUM(INSTLUMI) FROM CMS_RUNTIME_LOGGER.LUMI_SECTIONS A, CMS_UGT_MON.VIEW_LUMI_SECTIONS B WHERE PHYSICS_FLAG*BEAM1_PRESENT=1 AND A.RUNNUMBER=%s AND B.RUN_NUMBER(+)=A.RUNNUMBER AND B.LUMI_SECTION(+)=A.LUMISECTION AND A.LUMISECTION>=%s AND B.LUMI_SECTION>=%s AND A.LUMISECTION<=%s AND B.LUMI_SECTION<=%s""" % (sys.argv[2], sys.argv[3], sys.argv[3], sys.argv[4], sys.argv[4])
                

        print "num bunches colliding: ",bunches
        
        query = "SELECT SUM(A.PACCEPT), (SELECT M.NAME FROM CMS_HLT_GDR.U_PATHS M,CMS_HLT_GDR.U_PATHIDS L \
        WHERE L.PATHID=A.PATHID AND M.ID=L.ID_PATH) PATHNAME FROM CMS_RUNINFO.HLT_SUPERVISOR_TRIGGERPATHS A\
        WHERE RUNNUMBER=%s AND A.LSNUMBER>=%s AND A.LSNUMBER<=%s GROUP BY A.PATHID" % (sys.argv[2], sys.argv[3], sys.argv[4])


        self.curs.execute(query)
        self.lumicurs.execute(lumiquery)

        lumi = (float(self.lumicurs.fetchone()[0]))/(float(sys.argv[4])-float(sys.argv[3]))  #missing lumi skipped in numerator, but not denominator
        print "average luminosity is: ",lumi
        pu=lumi*80000/11246/bunches
        print "<PU> = ",pu
        
        for HLTPass, triggerName in self.curs.fetchall():
            my_arr = ['HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v1','HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelSeedMatch_Mass70_v1','HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_v1','HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55_v1','HLT_Diphoton30_18_Solid_R9Id_AND_IsoCaloId_AND_HE_R9Id_Mass55_v1']
            for path in my_arr: 
                if triggerName.find(path) > -1:
                    rate = float(HLTPass)/23.31041/(float(sys.argv[4]) - float(sys.argv[3])) #missing lumi skippe in numerator, but not denominator
                    print path," rate: ",rate
                    ratenorm = rate/lumi*1.2*10000
                    print path," rate normalized to 1.2e34 ",ratenorm
        
## ----------- End of class ------------ ##

if __name__ == "__main__":
    query_tool = DBQueryTool()
    query_tool.test_query()
