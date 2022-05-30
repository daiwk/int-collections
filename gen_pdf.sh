
#pandoc -N -s --toc --smart --latex-engine=xelatex -V CJKmainfont='Heiti SC' -V mainfont='Times New Roman' -V geometry:margin=1in -f markdown+markdown_in_html_blocks+raw_html-implicit_figures ./int.md -o ./int.pdf

function gen()
{
    fname=$1
    cat $fname.md | python change_for_pdf.py > $fname-pdf.md

    pandoc -N -s --toc --smart --latex-engine=xelatex -V CJKmainfont='Heiti SC' -V mainfont='Times New Roman' -V geometry:margin=1in --highlight-style tango -f markdown+markdown_in_html_blocks+raw_html-implicit_figures ./$fname-pdf.md -o ./$fname.pdf
}

gen int-summary
gen int-ml
