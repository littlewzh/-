USER := ？

.PHONY: zip rm git all

.DEFAULT_GOAL := all

all: zip git

zip:
	zip -r $(addsuffix .zip,$(USER)) Code/ parser README report.pdf

git:
	@git add -A --ignore-errors
	@while (test -e .git/index.lock); do sleep 0.1; done
	@(uname -a && uptime) | git commit -F - -q --no-verify --allow-empty
	@sync

rm:
	rm -f $(addsuffix .zip,$(USER))


