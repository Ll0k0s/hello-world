all: load save
save:
	git add .
	git commit -m "+update"
	git push

load:
 	git clone https://github.com/Ll0k0s/hello-world

