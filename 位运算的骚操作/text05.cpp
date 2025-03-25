/*逆序二进制的状态*/
int reverseBits(int n)
{
    /*
    设abcdefgh
    倒叙后
    hgfedcba
    过程
    先1v1交换
    ba dc fe hg
    再2v2交换
    dcba hgfe
    再4v4交换
    hgfedcba
    */
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    /*
    abcdefgh
    先与
    10101010与
    得
    a0c0e0g0

    abcdefgh
    再与
    01010101与
    得
    0b0d0f0h

    a0c0e0g0 >>1得
    0a0c0e0g

    0b0d0f0h <<1得
    b0d0f0h0

    0a0c0e0g 与
    b0d0f0h0 或
    badcfehg

    剩下的的代码一样的原理，晚上11点半了，我相信未来的我能理解的，剩下的不写注释了
    */

    n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
    n = (n >> 16) | (n << 16);
    return n;
}