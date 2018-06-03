#include "../ringbuf.h"
#include "gtest/gtest.h"

TEST(ringbuf, malloctest)
{
    ringbuf *rb = ringbuf_new(7);
    EXPECT_TRUE(rb == NULL);
    rb = ringbuf_new(8);
    EXPECT_TRUE(rb != NULL);
}

TEST(ringbuf, nodataread)
{
    ringbuf *rb = ringbuf_new(8);
    char buf[8] = {0};

    size_t sz = ringbuf_get(rb, buf, 2);
    EXPECT_EQ(sz, 0);
    EXPECT_STREQ(buf, "");
}

TEST(ringbuf, normal)
{
    ringbuf *rb = ringbuf_new(8);

    char buf[8] = {0};
    size_t sz = ringbuf_put(rb, "abc", 3);
    EXPECT_EQ(sz, 3);

    sz = ringbuf_get(rb, buf, 2);
    EXPECT_EQ(sz, 2);
    EXPECT_STREQ(buf, "ab");

    memset(buf, 0, sizeof(buf));
    sz = ringbuf_get(rb, buf, 100);
    EXPECT_EQ(sz, 1);
    EXPECT_STREQ(buf, "c");

    memset(buf, 0, sizeof(buf));
    sz = ringbuf_get(rb, buf, 3);
    EXPECT_EQ(sz, 0);
    EXPECT_STREQ(buf, "");
}

TEST(ringbuf, write_too_much)
{
    ringbuf *rb = ringbuf_new(8);
    char buf[16] = {0};

    const char *p = "1234567890";
    unsigned sz = ringbuf_put(rb, p, strlen(p));
    EXPECT_EQ(sz, 8);
    sz = ringbuf_get(rb, buf, 2);
    EXPECT_EQ(sz, 2);
    EXPECT_STREQ(buf, "12");

    sz = ringbuf_put(rb, p, strlen(p));
    EXPECT_EQ(sz, 2);

    sz = ringbuf_get(rb, buf, 16);
    EXPECT_EQ(sz, 8);
    EXPECT_STREQ(buf, "34567812");
}

TEST(ringbuf,  read_too_much)
{
    ringbuf *rb = ringbuf_new(8);

    char buf[16] = {0};
    const char *p = "1234567890";
    size_t sz = ringbuf_get(rb, buf, 10);
    EXPECT_EQ(sz, 0);
    EXPECT_STREQ(buf, "");

    sz = ringbuf_put(rb, "123", 2);
    EXPECT_EQ(sz, 2);
    sz = ringbuf_get(rb, buf, 3);
    EXPECT_EQ(sz, 2);
    EXPECT_STREQ(buf, "12");

    sz = ringbuf_put(rb, p, strlen(p));
    EXPECT_EQ(sz, 8);

    sz = ringbuf_get(rb, buf, 16);
    EXPECT_EQ(sz, 8);
    EXPECT_STREQ(buf, "12345678");

    sz = ringbuf_get(rb, buf, 1);
    EXPECT_EQ(sz, 0);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
