dir1 = /home/sokolhah/git/hello-world/kpi/dk62_sokol/
dir2 = debian@192.168.7.2:/home/debian/build/
namelab = lab3_kernel_threads

load_kpi:
	git clone https://github.com/Ll0k0s/kpi-embedded-linux-course
load_home:
	git clone https://github.com/Ll0k0s/hello-world

save:
	git add .
	git commit -m "+updates"
	git push
bb:
	sudo scp -r $(dir1)$(namelab)/ $(dir2)

