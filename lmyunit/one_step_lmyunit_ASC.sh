gmake -f Makefile.LmyUnit_DEBUG
api-sanity-checker -lib lmyunit -d lmyunit.xml  -gen 
api-sanity-checker -lib lmyunit -d lmyunit.xml  -build
api-sanity-checker -lib lmyunit -d lmyunit.xml  -run
