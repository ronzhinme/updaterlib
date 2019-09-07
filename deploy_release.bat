@echo off

set token=%1
set tagName=%2
set description=%3

curl -X DELETE -H "PRIVATE-TOKEN: %token%" -d tag_name=%tagName% --url "https://gitlab.com/api/v4/projects/12425924/releases/%tagName%"
curl -X POST -H "PRIVATE-TOKEN: %token%" -d name=%tagName% -d description=%description% -d tag_name=%tagName% --url "https://gitlab.com/api/v4/projects/12425924/releases"
curl -X POST -H "PRIVATE-TOKEN: %token%" -d name="linux" -d url="https://gitlab.com/ronme/appupdaterlib/-/jobs/artifacts/%tagName%/download?job=linux_build" --url "https://gitlab.com/api/v4/projects/12425924/releases/%tagName%/assets/links"
