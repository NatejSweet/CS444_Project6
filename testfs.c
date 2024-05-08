#include "image.h"
#include "block.h"
#include "ctest.h"
#include "free.h"
#include "inode.h"

void test_image_fd_init(void)
{
    CTEST_ASSERT(image_fd == -1, "Test image_fd is -1 before use");
}

void test_image_fd_gets_set(void)
{
    CTEST_ASSERT(image_fd != -1, "Test image_fd gets set once used");
}
void test_image_open(void)
{
    CTEST_ASSERT(image_open("sample.txt", 1) == 4, "Test image_open");
}

void test_image_close(void)
{
    CTEST_ASSERT(image_close() == 0, "Test image_close");
}

void test_bread(void)
{
    unsigned char blockMap[4096] = {1, 1, 1, 1, 1, 1};
    CTEST_ASSERT(bread(2, blockMap) == blockMap, "Test bread");
}
void test_bwrite(void)
{
    unsigned char tmp[4096] = {1, 1, 1, 1, 1, 0};
    bwrite(3, tmp);
    CTEST_ASSERT(bread(3, tmp) == tmp, "Test bwrite(write, then assert read)");
}

void test_set_free(void)
{
    unsigned char block[4096] = {0, 0, 0, 0, 0, 0};
    set_free(block, 1, 1);
    CTEST_ASSERT(block[0] == 1, "Test set_free");
}

void test_find_free(void)
{
    unsigned char block[4096] = {1, 0, 0, 0, 0, 0};
    CTEST_ASSERT(find_free(block) == 1, "Test find_free");
}

void test_ialloc(void)
{
    unsigned char inode_map[4096] = {0, 0, 0, 0, 0, 0};
    CTEST_ASSERT(ialloc(inode_map) == 0, "Test ialloc");
}

void test_alloc(void)
{
    unsigned char data_block[4096] = {0, 0, 0, 0, 0, 0};
    CTEST_ASSERT(alloc(data_block) == 0, "Test alloc");
}

#ifdef CTEST_ENABLE
int main()
{
    CTEST_VERBOSE(1);
    test_image_fd_init();
    image_open("sample.txt", 0);
    test_image_fd_gets_set();
    test_image_open();
    test_image_close();
    test_bread();
    test_bwrite();
    test_set_free();
    test_find_free();
    test_ialloc();
    test_alloc();
    CTEST_RESULTS();
    CTEST_EXIT();
    return 0;
}

#else
int main()
{
    // unsigned char superblock[4096];
    // unsigned char inode_map[4096];
    // unsigned char block_map[4096];
    // unsigned char inode0[4096];
    // unsigned char inode1[4096];
    // unsigned char inode2[4096];
    // unsigned char inode3[4096];
    // unsigned char file_data_block[4096];
    image_open("sample.txt", 0);
    unsigned char tmp[4096];
    bread(0, tmp);
    tmp[0] = 1;
    bwrite(0, tmp);
    bread(0, tmp);
    return 0;
}
#endif