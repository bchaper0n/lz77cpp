# [lz77](https://en.wikipedia.org/wiki/LZ77_and_LZ78) implementation in c++

lossless data compression algorithm by Abraham Lempel and Jacob Ziv in 1977

## implementation steps
1. suffix array (sorting using quick sort for now; [SA-IS](https://www.zork.net/~st/jottings/sais.html) todo)
2. dictionary of windows_size
3. encoder
4. decoder
