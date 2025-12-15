srpm:
	dnf install -y git rpm-build
	git archive --format=tar.gz --prefix=slither-$(VERSION)/ -o slither-$(VERSION).tar.gz HEAD
	rpmbuild -bs slither.spec \
		--define "_sourcedir $(CURDIR)" \
		--define "_srcrpmdir $(outdir)" \
		--define "version $(VERSION)"

.PHONY: srpm