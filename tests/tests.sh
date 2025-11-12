# run.sh
#!/usr/bin/env bash
find . -name "*fs" -print -exec ddforth -e {} \;
