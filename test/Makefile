SUBDIRS = client server
CURPATH = $(shell pwd)
.PHONY: all
all:
	echo $(CURPATH)
	@list='$(SUBDIRS)'; for subdir in $$list; do \
		echo "Clean in $$subdir";\
		cd $$subdir && $(MAKE) && cd $(CURPATH);\
		#$(MAKE) -f  $$subdir/Makefile;\
	done
 
.PHONY: clean
clean:
	@list='$(SUBDIRS)'; for subdir in $$list; do \
		echo "Clean in $$subdir";\
		cd $$subdir && $(MAKE) clean && cd $(CURPATH);\
		#$(MAKE) -f  $$subdir/Makefile clean;\
	done
