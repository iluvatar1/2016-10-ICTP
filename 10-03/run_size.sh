 for ((bsize = 1; bsize <= 8192; bsize = 2*bsize)); do
     echo -n "| $bsize | " ; 
     for level in 0 1 2 3; do 
         gcc fast_transpose_template.c -O${level}; 
         for reps in $(seq 1 20) ; do 
             ./a.out $bsize; done | awk 'BEGIN {MIN = 10000}  {if ($1 < MIN) MIN=$1 } END {printf "%s |", MIN}';  
     done; 
     echo ""; 
 done;
