sh -x gen_pdf.sh

grep offerNo ./int.md | awk -F'No' '{print $2}'| sort -n > progress.res.txt

git add ./src/*/*.cpp
git add ./assets
git add progress.res.txt
git add *.md
git add *.pdf
git add run.sh
git add commit.sh

git config --global user.name daiwk

git commit -m 'xx'
git push

