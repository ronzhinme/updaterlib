googleUrl="https://drive.google.com/uc?export=download%26id="
token=$1
tagName=$2
description=$3
winUrl_x32=$googleUrl$4
winUrl_x64=$googleUrl$5
linuxUrl=$googleUrl$6
macosUrl=$googleUrl$7

releaseUrl="https://gitlab.com/api/v4/projects/12425924/releases/"
releaseTagged=${releaseUrl}${tagName}
releaseLinks=${releaseTagged}"/assets/links"

curl -X DELETE -H "PRIVATE-TOKEN: ${token}" -d tag_name=${tagName} --url ${releaseTagged}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name=${tagName} -d description=${description} -d tag_name=${tagName} --url ${releaseUrl}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name="linux" -d url="${linuxUrl}" --url ${releaseLinks}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name="windows_x32" -d url="${winUrl_x32}" --url ${releaseLinks}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name="windows_x64" -d url="${winUrl_x64}" --url ${releaseLinks}
curl -X POST -H "PRIVATE-TOKEN: ${token}" -d name="mac" -d url="${macosUrl}" --url ${releaseLinks}


