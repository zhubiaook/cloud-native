count=$1
./mem_alloc $1 &
echo -1000 > /proc/$!/oom_score_adj
sleep 1000
