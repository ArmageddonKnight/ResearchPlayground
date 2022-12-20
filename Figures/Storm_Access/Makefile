PDFS := $(filter-out $(wildcard *-crop.pdf),$(wildcard *.pdf))
CROPPED_PDFS := $(PDFS:.pdf=-crop.pdf)

all: clean $(CROPPED_PDFS)

%-crop.pdf: %.pdf
	pdfcrop $<

.PHONY: clean
clean:
	$(RM) *-crop.pdf
