wc -l `find . \( \( -name '*.cpp' -or -name '*.hpp' \) -and -not \( -name '*exprtk*' -or -name '*qcustomplot*' \) \) -print`
