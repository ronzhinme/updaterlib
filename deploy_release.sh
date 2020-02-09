token=$1
tagName=$2
description=$3
winId=$4
linuxId=$5
macosId=$6

googleUrl="https://drive.google.com/uc?export=download%26id="
winUrl=${googleUrl}${winId}
linuxUrl=${googleUrl}${linuxId}
macosUrl=${googleUrl}${macosId}

releaseUrl="https://gitlab.com/api/v4/projects/12425924/releases/"
releaseTagged=${releaseUrl}${tagName}
releaseLinks=${releaseTagged}"/assets/links"

curl -X DELETE -H "PRIVATE-TOKEN: ${token}" -d tag_name=${tagName} --url ${releaseTagged}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name=${tagName} -d description=${description} -d tag_name=${tagName} --url ${releaseUrl}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name="linux" -d url="${linuxUrl}" --url ${releaseLinks}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name="windows" -d url="${winUrl}" --url ${releaseLinks}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name="mac" -d url="${macosUrl}" --url ${releaseLinks}


