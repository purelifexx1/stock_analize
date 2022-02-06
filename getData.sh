#!/bin/bash
# https://cafef1.mediacdn.vn/data/ami_data/20220121/CafeF.SolieuGD.Upto21012022.zip
# https://cafef1.mediacdn.vn/data/ami_data/20220124/CafeF.SolieuGD.Upto24012022.zip
# https://cafef1.mediacdn.vn/data/ami_data/20220121/CafeF.SolieuGD.Upto21012022.zip
# CafeF.SolieuGD.Upto05012022.zip

rm -fr stock_data
mkdir stock_data
cd stock_data

vari1=""
vari2=""
vari3=""
count_back=0
limit_count=0
while true
do
    vari1=$(date --date="-${count_back} days" "+%Y%m%d")
    vari2=$(date --date="-${count_back} days" "+%d%m%Y")
    vari3=$(date --date="-${count_back} days" "+%d.%m.%Y")
    echo "Download data up to date ${vari1}..."
    src_path="https://cafef1.mediacdn.vn/data/ami_data/${vari1}/CafeF.SolieuGD.Upto${vari2}.zip"
    wget ${src_path}
    if [[ $? == 0 ]]; then
        break
    fi
    let count_back++
    let limit_count++
    if [[ ${limit_count} == 10 ]]; then
        echo "Loop break after 10 attemps, no source data to be fetched"
        exit 1
    fi
done

zip_name=$(ls *.zip)
unzip ${zip_name}

mv "CafeF.HNX.Upto${vari3}.csv" HNX.csv
mv "CafeF.HSX.Upto${vari3}.csv" HSX.csv
mv "CafeF.UPCOM.Upto${vari3}.csv" UPCOM.csv

exit 0