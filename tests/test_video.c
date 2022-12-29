
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "i106_decode_video.h"
#include "unity.h"
#include "unity_fixture.h"


TEST_GROUP_RUNNER(test_decode_video){
    RUN_TEST_CASE(test_decode_video, Test_Decode_FirstVideoF0);
    RUN_TEST_CASE(test_decode_video, Test_Decode_NextVideoF0);
}


TEST_GROUP(test_decode_video);
TEST_SETUP(test_decode_video){}
TEST_TEAR_DOWN(test_decode_video){}


TEST(test_decode_video, Test_Decode_FirstVideoF0){
    SuI106Ch10Header header;
    void * buffer = malloc(32);
    SuVideoF0_CurrMsg msg;

    TEST_ASSERT_EQUAL(I106_OK, enI106_Decode_FirstVideoF0(&header, buffer, &msg));

    free(buffer);
}


TEST(test_decode_video, Test_Decode_NextVideoF0){
    SuI106Ch10Header header;
    SuVideoF0_CurrMsg msg;
    char * buffer = malloc(254);

    memset(buffer, 0, sizeof(SuVideoF0_CurrMsg));
    header.ulDataLen = 512;
    msg.pachTSData = (uint8_t *)buffer + 4;
    msg.psuChanSpec = (SuVideoF0_ChanSpec*)buffer;

    msg.psuChanSpec->bET = 0;

    TEST_ASSERT_EQUAL(I106_OK, enI106_Decode_NextVideoF0(&header, &msg));

    free(buffer);
}
