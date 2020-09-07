Thing to remember:
- had to split hit virticle and hit horizontal for scoring & due to overlap issue

tick 1: (approach)
speed: 5
```
.....
>|  |xxxx
>|  |xxxx
>|  |xxxx
```

tick 2: (overlap)
speed: 5
```
........
    |>>|xxx
    |>>|xxx
    |>>|xxx
```

tick 3: (overlap)
speed: -5
```
........
    |xxx
    |xxx
    |xxx
```
edges still overlap

tick 4: (overlap again)
speed: 5
```
........
    |>>|xxx
    |>>|xxx
    |>>|xxx
```
edges still overlap and it (mistakenly) reverses again.
