# Narthex Makefile
# GNU GPL v3.0

CC=gcc

#all: inc/nin.c enhance/nhan.c leet/nleet.c rev/nrev.sh
#	$(CC) enhance/nhan.c -o nhance
#	$(CC) inc/nin.c -o ninc
#	$(CC) leet/nleet.c -o nleet

install: inc/nin.c enhance/nhan.c leet/nleet.c rev/nrev.sh wiz/nwiz.sh inc/ninc.1 enhance/nhance.1 rev/nrev.1 leet/nleet.1
	$(CC) enhance/nhan.c -o nhance
	$(CC) inc/nin.c -o ninc
	$(CC) leet/nleet.c -o nleet
	sudo mv nhance /bin
	sudo mv ninc /bin
	sudo mv nleet /bin
	sudo mv rev/nrev.sh /bin/nrev
	sudo mv wiz/nwiz.sh /bin/nwiz
	mkdir -p /var/lib/narthex/
	cp wiz/elder.txt /var/lib/narthex/
	sudo cp enhance/nhance.1 /usr/share/man/man1
	sudo cp inc/ninc.1 /usr/share/man/man1
	sudo cp leet/nleet.1 /usr/share/man/man1
	sudo cp rev/nrev.1 /usr/share/man/man1
	sudo mandb

uninstall: /bin/ninc /bin/nhance /bin/nrev /bin/nleet /bin/nwiz /usr/share/man/man1/ninc.1 /usr/share/man/man1/nhance.1 /usr/share/man/man1/nrev.1 /usr/share/man/man1/nleet.1
	rm /bin/ninc /usr/share/man/man1/ninc.1
	rm /bin/nhance /usr/share/man/man1/nhance.1
	rm /bin/nleet /usr/share/man/man1/nleet.1
	rm /bin/nrev /usr/share/man/man1/nrev.1
	rm /bin/nwiz
	rm -r $${HOME}/.config/narthex/
