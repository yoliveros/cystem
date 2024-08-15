files := $(wildcard src/*.c)
p_name := cystem
exec := cm
c_version := c17
com_flg := -Wall -Werror -Wextra -pedantic -std=$(c_version)
dev_flg := -g $(com_flg)
dist_flg := -O2 $(com_flg) 

dev: $(files)
	@mkdir -p dev
	@echo 'Building Dev...'
	$(CC) $(files) -o dev/$(exec) $(dev_flg)

dist: $(files)
	@mkdir -p dist
	@echo 'Building Pord...'
	$(CC) $(files) -o dist/$(exec) $(dist_flg)

clean: 
	@rm -rf dev dist test
