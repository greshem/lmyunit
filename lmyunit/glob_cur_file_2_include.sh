#!/bin/bash
find unitcode/  |grep '\.h$' |sed 's/^/#include \"/g'  |sed 's/$/\"/g'  
