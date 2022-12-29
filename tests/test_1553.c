

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "i106_decode_1553f1.h"
#include "unity.h"
#include "unity_fixture.h"
#include <irig106ch10.h>


TEST_GROUP_RUNNER(test_1553){
    RUN_TEST_CASE(test_1553, TestDecodeFirst1553F1);
    RUN_TEST_CASE(test_1553, TestDecodeNext1553F1);
    RUN_TEST_CASE(test_1553, TestGetCommandWord);
    RUN_TEST_CASE(test_1553, TestMS1553WordCount);
}


TEST_GROUP(test_1553);
TEST_SETUP(test_1553){}
TEST_TEAR_DOWN(test_1553){}


TEST(test_1553, TestDecodeFirst1553F1){
    SuI106Ch10Header      header;
    EnI106Status          status;
    char                * buffer;
    Su1553F1_CurrMsg      msg;
    Su1553F1_ChanSpec     csdw;
    Su1553F1_Header       iph;
    int msg_size = sizeof(Su1553F1_CurrMsg) + 3;

    header.ulDataLen = sizeof(Su1553F1_ChanSpec) + (msg_size * 4);
    buffer = malloc(header.ulDataLen);
    csdw.uMsgCnt = 4;
    iph.uMsgLen = 3;

    memcpy(buffer, (void *)&csdw, sizeof(Su1553F1_ChanSpec));
    memcpy(buffer + sizeof(Su1553F1_ChanSpec), (void *)&iph, sizeof(Su1553F1_CurrMsg));

    status = enI106_Decode_First1553F1(&header, buffer, &msg);
    TEST_ASSERT_EQUAL(status, I106_OK);
    TEST_ASSERT_EQUAL(3, msg.psu1553Hdr->uMsgLen);

    free(buffer);
}


TEST(test_1553, TestDecodeNext1553F1){
    SuI106Ch10Header       header;
    EnI106Status           status;
    char                 * buffer;
    Su1553F1_CurrMsg       msg;
    Su1553F1_ChanSpec      csdw;
    Su1553F1_Header        iph;
    int msg_size = sizeof(Su1553F1_Header) + 3;
    int offset = 0;

    header.ulDataLen = sizeof(Su1553F1_ChanSpec) + (msg_size * 4);
    buffer = malloc(header.ulDataLen);
    csdw.uMsgCnt = 4;
    msg.psuChanSpec = &csdw;
    msg.ulCurrOffset = 0;
    msg.ulDataLen = header.ulDataLen;
    msg.uMsgNum = 0;
    iph.uMsgLen = 3;

    memcpy(buffer, (void *)&iph, sizeof(Su1553F1_Header));
    msg.psu1553Hdr = (Su1553F1_Header *)buffer;
    offset = sizeof(Su1553F1_Header) + iph.uMsgLen;

    iph.uMsgLen = 4;
    memcpy(buffer + offset, (void *)&iph, sizeof(Su1553F1_Header));

    status = enI106_Decode_Next1553F1(&msg);
    TEST_ASSERT_EQUAL(I106_OK, status);
    TEST_ASSERT_EQUAL(4, msg.psu1553Hdr->uMsgLen);

    free(buffer);
}


TEST(test_1553, TestGetCommandWord){
    SuCmdWord     cmd;
    unsigned int  * raw = (unsigned int *)&cmd;

    cmd.uRTAddr = 12;
    cmd.bTR = 0;
    cmd.uSubAddr = 20;
    cmd.uWordCnt = 15;
    TEST_ASSERT_EQUAL_STRING("12-R-20-15", szCmdWord(*raw));

    cmd.uRTAddr = 10;
    cmd.bTR = 1;
    cmd.uSubAddr = 21;
    cmd.uWordCnt = 0;
    TEST_ASSERT_EQUAL_STRING("10-T-21-32", szCmdWord(*raw));
}


TEST(test_1553, TestMS1553WordCount){
    SuCmdWordU cmd;

    // Subaddress 0 or 0x001f should return WordCount & 0x0010
    cmd.suStruct.uSubAddr = 0x0000;
    cmd.suStruct.uWordCnt = 17;
    TEST_ASSERT_EQUAL(1, i1553WordCnt((SuCmdWordU*)&cmd));
    cmd.suStruct.uWordCnt = 07;
    TEST_ASSERT_EQUAL(0, i1553WordCnt((SuCmdWordU*)&cmd));
    cmd.suStruct.uSubAddr = 0x001f;
    cmd.suStruct.uWordCnt = 17;
    TEST_ASSERT_EQUAL(1, i1553WordCnt((SuCmdWordU*)&cmd));
    cmd.suStruct.uWordCnt = 07;
    TEST_ASSERT_EQUAL(0, i1553WordCnt((SuCmdWordU*)&cmd));

    // Otherwise, should get WordCount (or 32 if WordCount is 0)
    cmd.suStruct.uSubAddr = 0x0010;
    cmd.suStruct.uWordCnt = 0;
    TEST_ASSERT_EQUAL(32, i1553WordCnt((SuCmdWordU*)&cmd));
    cmd.suStruct.uWordCnt = 24;
    TEST_ASSERT_EQUAL(24, i1553WordCnt((SuCmdWordU*)&cmd));
}
