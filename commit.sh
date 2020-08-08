sh -x gen_pdf.sh

grep offerNo ./int.md | awk -F'No' '{print $2}'| sort -n > progress.res.txt

git add .
git commit -m 'xx'
git push

