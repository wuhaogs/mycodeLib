/************************************************************************
Copyright (C), 2018-2020, Eastcom.All Rights Reserved.
File name��     easttest.c
Author��        wuh
Date�� 		    2018-06-19
Description��

Others��        None
History:
2018-06-19 wuh Created
*************************************************************************/


#include "etUtil.h"
#include "common.h"
#include "easttest.h"

/*��ȡpdt���Ź���0-�㽭��1-ȫ����2-���Թ���*/
static EUINT32 s_uiPdtDialRule = STANDARD_PDT_DIALING_RULE;

static EUINT32 s_uiPDTconstNP = 571;/*PDTĬ������*/
//static EUINT32 s_uiPDTconstFIN = 20;/*PDTĬ�϶Ӻ�*/

const NP_TABLE_t s_taddrnptable[] =
{
    {801, 800}, {802, 800}, {803, 800}, {800, 800}, {361, 360}, {362, 360}, {363, 360}, {360, 360}, {329, 328}, {330, 328}, {331, 328},
    {328, 328}, {624, 623}, {625, 623}, {626, 623}, {623, 623}, {336, 334}, {337, 334}, {338, 334}, {339, 334}, {340, 334}, {341, 334},
    {342, 334}, {343, 334}, {344, 334}, {345, 334}, {335, 334}, {334, 334}, {351, 348}, {349, 348}, {352, 348}, {353, 348}, {354, 348},
    {355, 348}, {356, 348}, {357, 348}, {358, 348}, {359, 348}, {350, 348}, {348, 348}, {371, 390}, {372, 390}, {373, 390}, {374, 390},
    {375, 390}, {376, 390}, {377, 390}, {378, 390}, {379, 390}, {391, 390}, {370, 390}, {392, 390}, {393, 390}, {394, 390}, {395, 390},
    {396, 390}, {398, 390}, {390, 390}, {420, 422}, {410, 422}, {411, 422}, {412, 422}, {413, 422}, {414, 422}, {415, 422}, {416, 422},
    {417, 422}, {418, 422}, {419, 422}, {421, 422}, {427, 422}, {429, 422}, {422, 422}, {431, 430}, {432, 430}, {433, 430}, {434, 430},
    {435, 430}, {436, 430}, {437, 430}, {438, 430}, {439, 430}, {430, 430}, {451, 450}, {452, 450}, {453, 450}, {454, 450}, {455, 450},
    {456, 450}, {457, 450}, {459, 450}, {464, 450}, {467, 450}, {458, 450}, {468, 450}, {469, 450}, {450, 450}, {471, 480}, {472, 480},
    {473, 480}, {474, 480}, {475, 480}, {476, 480}, {477, 480}, {478, 480}, {479, 480}, {470, 480}, {482, 480}, {483, 480}, {480, 480},
    {525, 520}, {510, 520}, {511, 520}, {512, 520}, {513, 520}, {514, 520}, {515, 520}, {516, 520}, {517, 520}, {518, 520}, {519, 520},
    {523, 520}, {527, 520}, {520, 520}, {531, 540}, {532, 540}, {533, 540}, {534, 540}, {535, 540}, {536, 540}, {537, 540}, {538, 540},
    {539, 540}, {530, 540}, {543, 540}, {546, 540}, {631, 540}, {632, 540}, {633, 540}, {634, 540}, {635, 540}, {540, 540}, {551, 560},
    {552, 560}, {553, 560}, {554, 560}, {555, 560}, {556, 560}, {557, 560}, {558, 560}, {567, 560}, {559, 560}, {550, 560}, {561, 560},
    {562, 560}, {563, 560}, {564, 560}, {565, 560}, {566, 560}, {560, 560}, {571, 581}, {572, 581}, {573, 581}, {574, 581}, {575, 581},
    {576, 581}, {577, 581}, {578, 581}, {579, 581}, {570, 581}, {580, 581}, {581, 581}, {591, 590}, {592, 590}, {593, 590}, {594, 590},
    {595, 590}, {596, 590}, {597, 590}, {598, 590}, {599, 590}, {590, 590}, {721, 720}, {710, 720}, {711, 720}, {712, 720}, {713, 720},
    {714, 720}, {715, 720}, {716, 720}, {717, 720}, {718, 720}, {719, 720}, {722, 720}, {724, 720}, {726, 720}, {727, 720}, {728, 720},
    {720, 720}, {731, 740}, {732, 740}, {733, 740}, {734, 740}, {735, 740}, {736, 740}, {737, 740}, {738, 740}, {739, 740}, {730, 740},
    {743, 740}, {744, 740}, {745, 740}, {746, 740}, {740, 740}, {666, 667}, {660, 667}, {662, 667}, {663, 667}, {668, 667}, {750, 667},
    {751, 667}, {752, 667}, {753, 667}, {754, 667}, {755, 667}, {756, 667}, {757, 667}, {758, 667}, {759, 667}, {760, 667}, {762, 667},
    {763, 667}, {766, 667}, {768, 667}, {769, 667}, {667, 667}, {771, 780}, {772, 780}, {773, 780}, {774, 780}, {775, 780}, {776, 780},
    {777, 780}, {778, 780}, {779, 780}, {770, 780}, {781, 780}, {782, 780}, {783, 780}, {784, 780}, {780, 780}, {791, 789}, {701, 789},
    {792, 789}, {793, 789}, {794, 789}, {795, 789}, {796, 789}, {797, 789}, {798, 789}, {799, 789}, {790, 789}, {789, 789}, {600, 620},
    {601, 620}, {602, 620}, {603, 620}, {604, 620}, {605, 620}, {606, 620}, {607, 620}, {608, 620}, {609, 620}, {610, 620}, {611, 620},
    {612, 620}, {613, 620}, {614, 620}, {615, 620}, {616, 620}, {617, 620}, {618, 620}, {619, 620}, {621, 620}, {620, 620}, {486, 485},
    {487, 485}, {488, 485}, {489, 485}, {490, 485}, {491, 485}, {492, 485}, {493, 485}, {494, 485}, {485, 485}, {641, 640}, {691, 640},
    {692, 640}, {642, 640}, {643, 640}, {644, 640}, {645, 640}, {646, 640}, {647, 640}, {648, 640}, {649, 640}, {650, 640}, {651, 640},
    {652, 640}, {653, 640}, {654, 640}, {640, 640}, {381, 380}, {382, 380}, {383, 380}, {384, 380}, {385, 380}, {386, 380}, {387, 380},
    {380, 380}, {696, 700}, {697, 700}, {698, 700}, {700, 700}, {401, 400}, {402, 400}, {403, 400}, {404, 400}, {405, 400}, {406, 400},
    {407, 400}, {408, 400}, {409, 400}, {399, 400}, {400, 400}, {496, 495}, {497, 495}, {498, 495}, {499, 495}, {500, 495}, {501, 495},
    {502, 495}, {503, 495}, {504, 495}, {505, 495}, {506, 495}, {507, 495}, {508, 495}, {509, 495}, {495, 495}, {703, 702}, {704, 702},
    {705, 702}, {706, 702}, {707, 702}, {702, 702}, {441, 440}, {442, 440}, {443, 440}, {444, 440}, {445, 440}, {446, 440}, {447, 440},
    {448, 440}, {449, 440}, {440, 440}, {671, 670}, {672, 670}, {673, 670}, {674, 670}, {675, 670}, {676, 670}, {677, 670}, {678, 670},
    {679, 670}, {680, 670}, {681, 670}, {682, 670}, {683, 670}, {684, 670}, {685, 670}, {686, 670}, {670, 670}, {657, 656}, {656, 656},
    {659, 658}, {658, 658}, {586, 585}, {587, 585}, {588, 585}, {585, 585}, {804, 804}
};

/**************************************************************************
Function:GetProvinceNpFromTable
Description:�ӱ������Ż�ȡʡ���򹫰�������
Input:
Output:
Return:
***************************************************************************/
EINT32 GetProvinceNpFromTable(EUINT32 uiNpIn, EUINT32 *puiNpOut)
{
    EUINT32 i, uiNum = sizeof(s_taddrnptable) / sizeof(NP_TABLE_t);

    if(puiNpOut == NULL)
    {
        return ETERROR;
    }

    for(i = 0; i < uiNum; i++)
    {
        if(s_taddrnptable[i].uicurNP == uiNpIn)
        {
            *puiNpOut = s_taddrnptable[i].uipNP;
            return ETOK;
        }
    }
    return ETERROR;
}

/***********************************************************************
* Function   : AllCallUserNumToID
* Description:ȫ���û�����ת�տں���
* Input      :   EUINT32 uiUserNum�û�����
* Output     :  EUINT32 *puiID,�տں���
* Return     :�ɹ�����0��ʧ�ܷ���-1
* Others     : ��δʹ��
************************************************************************/
EINT32 AllCallUserNumToID(EUINT32 uiUserNum, EUINT32 *puiID)
{
    EUINT32 uiPnp = 0;/*ʡnp*/
    EINT32 iRet = ETOK;

    if((uiUserNum >= ADDR_ALL_NUMBER_4_MIN) && (uiUserNum <= ADDR_ALL_NUMBER_4_MAX)
            && (uiUserNum != ADDR_ALL_NUMBER_4_MAX - 1))
    {
        *puiID = ADDR_ALL_ID_4;
    }
    else if((uiUserNum >= ADDR_ALL_NUMBER_5_MIN) && (uiUserNum <= ADDR_ALL_NUMBER_5_MAX)
            && (uiUserNum != ADDR_ALL_NUMBER_5_MAX - 1))
    {
        *puiID = ADDR_ALL_ID_5;
    }
    else if((uiUserNum >= ADDR_ALL_NUMBER_6_MIN) && (uiUserNum <= ADDR_ALL_NUMBER_6_MAX)
            && (uiUserNum != ADDR_ALL_NUMBER_6_MAX - 1))
    {
        *puiID = ADDR_ALL_ID_6;
    }
    else if((uiUserNum >= ADDR_ALL_NUMBER_7_MIN) && (uiUserNum <= ADDR_ALL_NUMBER_7_MAX)
            && (uiUserNum != ADDR_ALL_NUMBER_7_MAX - 1))
    {
        *puiID = ADDR_ALL_ID_7;
    }
    else if((uiUserNum >= ADDR_ALL_NUMBER_8_MIN) && (uiUserNum <= ADDR_ALL_NUMBER_8_MAX)
            && (uiUserNum != ADDR_ALL_NUMBER_8_MAX - 1))
    {
        *puiID = ADDR_ALL_ID_8;
    }
    else if((uiUserNum >= ADDR_ALL_NUMBER_3_MIN) && (uiUserNum <= ADDR_ALL_NUMBER_3_MAX)
            && (uiUserNum != ADDR_ALL_NUMBER_3_MAX - 1))
    {
        if(s_uiPDTconstNP != ADDR_NP_PDT_POLICE) /*���ǲ���NP����ʧ��*/
        {
            return ETERROR;
        }

        iRet = GetProvinceNpFromTable(s_uiPDTconstNP, &uiPnp);/*����addr_np_table����curNp��Ӧ��pNP*/
        if(ETERROR == iRet)
        {
            return ETERROR;
        }

        *puiID = (uiPnp - ADDR_ALL_ID_123_NP_BASE) * 0x8000 + ADDR_ALL_ID_123_BASE1;
    }
    else if((uiUserNum >= ADDR_ALL_NUMBER_2_MIN) && (uiUserNum <= ADDR_ALL_NUMBER_2_MAX)
            && (uiUserNum != ADDR_ALL_NUMBER_2_MAX - 1))
    {
        iRet = GetProvinceNpFromTable(s_uiPDTconstNP, &uiPnp);/*����addr_np_table����curNp��Ӧ��pNP*/
        if(iRet != ETOK || uiPnp != s_uiPDTconstNP || s_uiPDTconstNP == ADDR_NP_PDT_POLICE) /*����ʡ��NP����ʧ��*/
        {
            return ETERROR;
        }

        *puiID = (uiPnp - ADDR_ALL_ID_123_NP_BASE) * 0x8000 + ADDR_ALL_ID_123_BASE1;
    }
    else if((uiUserNum >= ADDR_ALL_NUMBER_1_MIN) && (uiUserNum <= ADDR_ALL_NUMBER_1_MAX)
            && (uiUserNum != ADDR_ALL_NUMBER_1_MAX - 1))
    {
        iRet = GetProvinceNpFromTable(s_uiPDTconstNP, &uiPnp);/*����addr_np_table����curNp��Ӧ��pNP*/
        if(iRet != ETOK)
        {
            return ETERROR;
        }

        if(uiPnp == s_uiPDTconstNP)
        {
            *puiID = (s_uiPDTconstNP - ADDR_ALL_ID_123_NP_BASE) * 0x8000 + ADDR_ALL_ID_123_BASE2;
        }
        else if(uiPnp != s_uiPDTconstNP)
        {
            *puiID = (s_uiPDTconstNP - ADDR_ALL_ID_123_NP_BASE) * 0x8000 + ADDR_ALL_ID_123_BASE1;
        }
        else
        {
            return ETERROR;
        }
    }
    else
    {
        return ETERROR;
    }

    return ETOK;
}

/***********************************************************************
* Function   : IsAreaCallForID
* Description:�鿴�տں����Ƿ�Ϊȫ������
* Input      :   EUINT32 uiID�տں���
* Output     : EUINT32 *puiUserNum�û�����
* Return     :�ɹ�����0��ʧ�ܷ���-1
* Others     : ��δʹ��
************************************************************************/
EINT32 IsAreaCallForID(EUINT32 uiID, EUINT32 uiPriority, EUINT32 *puiUserNum)
{
    EINT32 iRet = ETERROR;
    EUINT32 uiNai = 0;
    EUINT32 uiSsi = 0;
    EUINT32 uiNp = 0;
    EUINT32 uiTmp = 0;/*��ʱ���*/

    if(NULL == puiUserNum)
    {
        return ETERROR;
    }

    uiNai = uiID >> ADDR_NP_OFFSET;
    uiSsi = uiID & ADDR_LOW15BIT_MAX;

    switch(uiID)
    {
        case ADDR_ALL_ID_8:  /*ȫ�����е�ַ  ��ͨ����ȫ�� *1987  ��������ȫ�� *1982*/
            *puiUserNum = ADDR_ALL_NUMBER_8_MAX;
            break;

        case ADDR_ALL_ID_7:  /*����ȫ�� ��ͨ����ȫ�� *1977  ��������ȫ�� *1972*/
            *puiUserNum = ADDR_ALL_NUMBER_7_MAX;
            break;

        case ADDR_ALL_ID_6:  /*����ȫ�� ��ͨ����ȫ�� *1967  ��������ȫ�� *1962*/
            *puiUserNum = ADDR_ALL_NUMBER_6_MAX;
            break;

        case ADDR_ALL_ID_5:  /*��վȫ�� ��ͨ����ȫ�� *1957  ��������ȫ�� *1952*/
            *puiUserNum = ADDR_ALL_NUMBER_5_MAX;
            break;

        case ADDR_ALL_ID_4: /*�Զ���ȫ�� ��ͨ����ȫ�� *1947  ��������ȫ�� *1942*/
            *puiUserNum = ADDR_ALL_NUMBER_4_MAX;
            break;

        default:   /*��̬�����ȫ������ȫ������*/
        {
            if((ADDR_ALL_DYN_NUMBER_MASK1 == uiSsi || ADDR_ALL_DYN_NUMBER_MASK2 == uiSsi)
                    && (uiNai >= ADDR_ALL_DYN_NUMBER_FORWARD_MIN && uiNai <= ADDR_ALL_DYN_NUMBER_FORWARD_MAX))
            {
                if(ADDR_ALL_DYN_NUMBER_MASK2 == uiSsi)
                {
                    uiNp = ((uiID - ADDR_ALL_ID_123_BASE1) >> ADDR_NP_OFFSET) + ADDR_ALL_ID_123_NP_BASE;
                    iRet = GetProvinceNpFromTable(uiNp, &uiTmp);
                    if(ETOK == iRet && uiNp == uiTmp)
                    {
                        *puiUserNum = ADDR_ALL_NUMBER_1_MAX;
                    }
                    else
                    {
                        return ETERROR;
                    }
                }
                else if(ADDR_ALL_DYN_NUMBER_MASK1 == uiSsi)
                {
                    uiNp = ((uiID - ADDR_ALL_ID_123_BASE1) >> ADDR_NP_OFFSET) + ADDR_ALL_ID_123_NP_BASE;
                    iRet = GetProvinceNpFromTable(uiNp, &uiTmp);

                    if(ETOK != iRet)
                    {
                        return ETERROR;
                    }

                    if(uiNp == uiTmp && ADDR_NP_PDT_POLICE != uiNp)
                    {
                        *puiUserNum = ADDR_ALL_NUMBER_2_MAX;
                        return ETOK;
                    }

                    if(uiNp == uiTmp && ADDR_NP_PDT_POLICE == uiNp)
                    {
                        *puiUserNum = ADDR_ALL_NUMBER_3_MAX;
                        return ETOK;
                    }

                    *puiUserNum = ADDR_ALL_NUMBER_1_MAX;
                }
            }
            else
            {
                return ETERROR;
            }
        }
        break;
    }

    if(EMERGENCY_CALL == uiPriority)
    {
        *puiUserNum -= 5;
    }

    return ETOK;
}

/***********************************************************************
* Function   : StandardPdtGroupIDToUserNum
* Description: ��׼pdt�տ����תΪ�û�����
* Input      :   EUINT32 uiID, �տں���
* Output     :EUINT32 *puiUserNum�û�����
* Return     :�ɹ�����ETOK��ʧ�ܷ���ETERROR
* Others     : ��δʹ��
************************************************************************/
EINT32 StandardPdtGroupIDToUserNum(EUINT32 uiID, EUINT32 uiPriority, EUINT32 *puiUserNum)
{
    EUINT32 uiNai = 0;/*ȫ����ʶ����*/
    EUINT32 uiSgi = 0;/*��տں�*/
    EUINT32 uiNp = 0;/*����*/
    EUINT32 uiFgn = 0;/*�Ӻ�*/
    EUINT32 uiLevel = 0;/*�ּ������level*/
    EUINT32 uiIn = 0;/*����*/
    EUINT32 uiTmpValue = 0;/*��ʱ��Ž��*/
    EINT32 iRet = ETOK;

    if(NULL == puiUserNum)
    {
        return ETERROR;
    }

    iRet = IsAreaCallForID(uiID, uiPriority, &uiTmpValue);
    if(ETERROR != iRet)
    {
        *puiUserNum = uiTmpValue;
        return ETOK;
    }

    uiNai = uiID >> ADDR_NP_OFFSET;/*ǰ9bitΪȫ����ʶ����*/
    uiSgi = uiID & ADDR_LOW15BIT_MAX;/*��15bitΪ�����ַ��*/

    if(uiNai < ADDR_NAI_PDT_MIN || uiNai > ADDR_NAI_PDT_MAX)
    {
        return ETERROR;
    }

    uiNp = uiNai + ADDR_NP_BASE;

    if(uiSgi >= ADDR_SGI_GRP_MIN && uiSgi <= ADDR_SGI_GRP_MAX) /*�ζ����*/
    {
        uiFgn = (uiSgi - 1) / 100 + ADDR_FORMAT_GRP_MIN;
        uiIn = (uiSgi - 1) % 100 + ADDR_NUM_GRP_MIN;

        if((uiFgn < ADDR_FORMAT_GRP_MIN || uiFgn > ADDR_FORMAT_GRP_MAX)
                || (uiIn < ADDR_NUM_GRP_MIN || uiIn > ADDR_NUM_GRP_MAX))
        {
            return ETERROR;
        }

        *puiUserNum = uiNp * 100000 + uiFgn * 1000 + uiIn;
    }
    else if(uiSgi >= ADDR_SGI_LVL_GRP_MIN && uiSgi <= ADDR_SGI_LVL_GRP_MAX) /*�ּ����*/
    {
        uiLevel = (uiSgi - ADDR_SGI_LVL_GRP_MIN) / 1000;
        uiIn = (uiSgi - ADDR_SGI_LVL_GRP_MIN) % 1000;

        if(uiLevel > 9 || (1 <= uiLevel && uiLevel <= 6))
        {
            return ETERROR;
        }

        *puiUserNum = uiNp * 100000 + 9 * 10000 + uiLevel * 1000 + uiIn;
    }
    else
    {
        return ETERROR;
    }

    return ETOK;
}
/***********************************************************************
* Function   : StandardPdtInvIDToUserNum
* Description: ��׼pdt�տڸ���תΪ�û�����
* Input      :   EUINT32 uiID, �տں���
* Output     :EUINT32 *puiUserNum�û�����
* Return     :�ɹ�����ETOK��ʧ�ܷ���ETERROR
* Others     : ��δʹ��
************************************************************************/
EINT32 StandardPdtInvIDToUserNum(EUINT32 uiID, EUINT32 *puiUserNum)
{
    EUINT32 uiNai = 0;/*ȫ����ʶ����*/
    EUINT32 uiSgi = 0;/*��տں�*/
    EUINT32 uiNp = 0;/*����*/
    EUINT32 uiFgn = 0;/*�Ӻ�*/
    EUINT32 uiIn = 0;/*����*/

    if(NULL == puiUserNum)
    {
        return ETERROR;
    }

    uiNai = uiID >> ADDR_NP_OFFSET;/*ǰ9bitΪȫ����ʶ����*/
    uiSgi = uiID & ADDR_LOW15BIT_MAX;/*��15bitΪ�����ַ��*/

    if(uiNai < ADDR_NAI_PDT_MIN || uiNai > ADDR_NAI_PDT_MAX)
    {
        return ETERROR;
    }

    uiNp = uiNai + ADDR_NP_BASE;

    if(uiSgi >= ADDR_SSI_IND_1_MIN && uiSgi <= ADDR_SSI_IND_1_MAX) /*����һ�Ӻ���*/
    {
        uiFgn = (uiSgi - ADDR_SSI_IND_1_MIN) / ADDR_TEAM1_LEN + ADDR_FORMAT_IND_1_MIN;
        uiIn = (uiSgi - ADDR_SSI_IND_1_MIN) % ADDR_TEAM1_LEN + ADDR_NUM_IND_1_MIN;

        if((uiFgn < ADDR_FORMAT_IND_1_MIN || uiFgn > ADDR_FORMAT_IND_1_MAX)
                || (uiIn < ADDR_NUM_IND_1_MIN || uiIn > ADDR_NUM_IND_1_MAX))
        {
            return ETERROR;
        }

        *puiUserNum = uiNp * 100000 + uiFgn * 1000 + uiIn;
    }
    else if(uiSgi >= ADDR_SSI_IND_2_MIN && uiSgi <= ADDR_SSI_IND_2_MAX) /*�������Ӻ���*/
    {
        uiFgn = (uiSgi - ADDR_SSI_IND_2_MIN) / ADDR_TEAM2_LEN + ADDR_FORMAT_IND_2_MIN;
        uiIn = (uiSgi - ADDR_SSI_IND_2_MIN) % ADDR_TEAM2_LEN + ADDR_NUM_IND_2_MIN;

        if((uiFgn < ADDR_FORMAT_IND_2_MIN || uiFgn > ADDR_FORMAT_IND_2_MAX)
                || (uiIn < ADDR_NUM_IND_2_MIN || uiIn > ADDR_NUM_IND_2_MAX))
        {
            return ETERROR;
        }

        *puiUserNum = uiNp * 100000 + uiFgn * 1000 + uiIn;
    }
    else if(uiSgi >= ADDR_SSI_DCN_MIN && uiSgi <= ADDR_SSI_DCN_MAX) /*����̨����*/
    {
        uiIn = uiSgi - ADDR_SSI_DCN_MIN + ADDR_NUM_DCN_MIN;

        if(uiIn < ADDR_NUM_DCN_MIN || ADDR_NUM_DCN_MAX < uiIn)
        {
            return ETERROR;
        }

        *puiUserNum = uiNp * 1000 + uiIn;
    }
    else if(uiSgi >= ADDR_SSI_SSN_MIN && uiSgi <= ADDR_SSI_SSN_MAX) /*�ط�̨����*/
    {
        uiIn = uiSgi - ADDR_SSI_SSN_MIN + ADDR_NUM_SSN_MIN;

        if(uiIn < ADDR_NUM_SSN_MIN || ADDR_NUM_SSN_MAX < uiIn)
        {
            return ETERROR;
        }

        *puiUserNum = uiNp * 1000 + uiIn;
    }
    else if(uiSgi >= ADDR_SSI_INT_MIN && uiSgi <= ADDR_SSI_INT_MAX) /*�ڲ����ߺ���*/
    {
        uiIn = uiSgi - ADDR_SSI_INT_MIN + ADDR_NUM_INT_MIN;

        if(uiIn < ADDR_NUM_INT_MIN || ADDR_NUM_INT_MAX < uiIn)
        {
            return ETERROR;
        }

        *puiUserNum = uiNp * 10000 + uiIn;
    }
    else
    {
        return ETERROR;
    }

    return ETOK;
}

/***********************************************************************
* Function   : ZJPdtGroupIDToUserNum
* Description: �㽭pdt�տ����תΪ�û�����
* Input      :   EUINT32 uiID, �տں���
* Output     :EUINT32 *puiUserNum�û�����
                   5-pabx������6-pabx���
* Return     :�ɹ�����ETOK��ʧ�ܷ���ETERROR
* Others     : ��δʹ��
************************************************************************/
EINT32 ZJPdtGroupIDToUserNum(EUINT32 uiID, EUINT32 uiPriority, EUINT32 *puiUserNum)
{
    EUINT32 uiNai = 0;/*ȫ����ʶ����*/
    EUINT32 uiSgi = 0;/*��տں�*/
    EUINT32 uiNp = 0;/*����*/
    EUINT32 uiLevel = 0;/*�ּ������level*/
    EUINT32 uiIn = 0;/*����*/
    EUINT32 uiTmpValue = 0;/*��ʱ��Ž��*/
    EINT32 iRet = ETOK;

    if(NULL == puiUserNum)
    {
        return ETERROR;
    }

    iRet = IsAreaCallForID(uiID, uiPriority, &uiTmpValue);
    if(ETERROR != iRet)
    {
        *puiUserNum = uiTmpValue;
        return ETOK;
    }

    uiNai = uiID >> ADDR_NP_OFFSET;/*ǰ9bitΪȫ����ʶ����*/
    uiSgi = uiID & ADDR_LOW15BIT_MAX;/*��15bitΪ�����ַ��*/

    if(uiNai < ADDR_NAI_PDT_MIN || uiNai > ADDR_NAI_PDT_MAX)
    {
        return ETERROR;
    }

    uiNp = uiNai + ADDR_NP_BASE;

    if(uiSgi < ADDR_SGI_LVL_GRP_MIN || uiSgi > ADDR_SGI_LVL_GRP_MAX)
    {
        return ETERROR;
    }

    /*7001-17000Ϊ�ּ���ź����*/
    uiLevel = (uiSgi - ADDR_SGI_LVL_GRP_MIN) / 1000;
    uiIn = (uiSgi - ADDR_SGI_LVL_GRP_MIN) % 1000;

    if(uiLevel > 9)
    {
        return ETERROR;
    }


    *puiUserNum = uiNp * 100000 + 9 * 10000 + uiLevel * 1000 + uiIn;

    return ETOK;
}

/***********************************************************************
* Function   : ZJPdtInvIDToUserNum
* Description: �㽭pdt�տڸ���תΪ�û�����
* Input      :   EUINT32 uiID, �տں���
* Output     :EUINT32 *puiUserNum�û�����
* Return     :�ɹ�����ETOK��ʧ�ܷ���ETERROR
* Others     : ��δʹ��
************************************************************************/
EINT32 ZJPdtInvIDToUserNum(EUINT32 uiID, EUINT32 *puiUserNum)
{
    EUINT32 uiNai = 0;/*ȫ����ʶ����*/
    EUINT32 uiSsi = 0;/*��տں�*/
    EUINT32 uiNp = 0;/*����*/
    EUINT32 uiIn = 0;/*����*/

    if(NULL == puiUserNum)
    {
        return ETERROR;
    }

    uiNai = uiID >> ADDR_NP_OFFSET;/*ǰ9bitΪȫ����ʶ����*/
    uiSsi = uiID & ADDR_LOW15BIT_MAX;/*��15bit������ַ��*/

    if(uiNai < ADDR_NAI_PDT_MIN || uiNai > ADDR_NAI_PDT_MAX)
    {
        return ETERROR;
    }

    uiNp = uiNai + ADDR_NP_BASE;

    if(0 == uiSsi || uiSsi > ADDR_NUM_IND_ZJP_MAX_4) /*���Ź����ĵ�����д�����ֵ��32200(����������32767)*/
    {
        return ETERROR;
    }

    uiIn = uiSsi;

    *puiUserNum = uiNp * 100000 + uiIn;

    return ETOK;
}
/***********************************************************************
* Function   : ConvertGroupIDToUserNumber
* Description: ���տ����תΪ�û�����
* Input      :   EUINT32 uiID�տں���
* Output     :EUINT32 *puiUserNum�û�����
* Others     : ��δʹ��
************************************************************************/
EINT32 ConvertGroupIDToUserNumber(EUINT32 uiID, EUINT32 uiPriority, EUINT32 *puiUserNum)
{
    EUINT32 uiNai = 0;/*ȫ����ʶ����*/
    EINT32 iRet = 0;

    uiNai = uiID >> ADDR_NP_OFFSET;/*ȡ�տں����ǰ9λ��0-31��ʾmpt��32-511Ϊpdt*/

    if(uiNai < ADDR_NAI_PDT_MIN)
    {
        return ETERROR;
    }

    if(ZJ_PDT_DIALING_RULE == s_uiPdtDialRule) /*�㽭ʡ���Ź���*/
    {
        iRet = ZJPdtGroupIDToUserNum(uiID, uiPriority, puiUserNum);
        if(ETERROR == iRet)
        {
            return ETERROR;
        }
    }
    else if(STANDARD_PDT_DIALING_RULE == s_uiPdtDialRule
            || INGORE_PDT_DIALING_RULE == s_uiPdtDialRule)/*���˲��Ź���ͺ��Բ��Ź���*/
    {
        iRet = StandardPdtGroupIDToUserNum(uiID, uiPriority, puiUserNum);
        if(ETERROR == iRet)
        {
            return ETERROR;
        }
    }
    else
    {
        return ETERROR;
    }

    return ETOK;
}

/***********************************************************************
* Function   : ConvertInvIDToUserNumber
* Description: ���տڸ���תΪ�û�����
* Input      :   EUINT32 uiID�տں���
* Output     :EUINT32 *puiUserNum�û�����
* Return     :�ɹ�����ETOK��ʧ�ܷ���ETERROR
* Others     : ��δʹ��
************************************************************************/
EINT32 ConvertInvIDToUserNumber(EUINT32 uiID, EUINT32 *puiUserNum)
{
    EUINT32 uiNai = 0;/*ȫ����ʶ����*/
    EINT32 iRet = 0;

    uiNai = uiID >> ADDR_NP_OFFSET;/*ȡ�տں����ǰ9λ��0-31��ʾmpt��32-511Ϊpdt*/

    if(uiNai < ADDR_NAI_PDT_MIN)
    {
        return ETERROR;
    }

    if(ZJ_PDT_DIALING_RULE == s_uiPdtDialRule) /*�㽭ʡ���Ź���*/
    {
        iRet = ZJPdtInvIDToUserNum(uiID, puiUserNum);
        if(ETERROR == iRet)
        {
            return ETERROR;
        }
    }
    else if(STANDARD_PDT_DIALING_RULE == s_uiPdtDialRule
            || INGORE_PDT_DIALING_RULE == s_uiPdtDialRule)/*���˲��Ź���ͺ��Բ��Ź���*/
    {
        iRet = StandardPdtInvIDToUserNum(uiID, puiUserNum);
        if(ETERROR == iRet)
        {
            return ETERROR;
        }
    }
    else
    {
        return ETERROR;
    }


    return ETOK;
}
/***********************************************************************
* Function   : GetDialerIndNumberByAirID
* Description: ���ݿտڸ��Ż�ȡ���Ŵ�����
* Input      : EUINT32 uiAirIndID �տڸ�����
* Output     : None
* Return     : ʧ�ܷ���ETERROR,�ɹ����ز��Ŵ�����
* Others     : ����,����16515073,����80020200
************************************************************************/
EUINT32 GetDialerIndNumberByAirID(EUINT32 uiAirIndID)
{
    EUINT32 uiDialerIndNum = 0;

    if( ETERROR == ConvertInvIDToUserNumber(uiAirIndID,&uiDialerIndNum))
    {
        uiDialerIndNum = 0;
    }
    return uiDialerIndNum;
}
/***********************************************************************
* Function   : GetDialerGrpNumberByAirID
* Description: ���ݿտ���Ż�ȡ���Ŵ����
* Input      : EUINT32 uiAirGrpID �տ������
* Output     : None
* Return     : ʧ�ܷ���ETERROR,�ɹ����ز��Ŵ�����
* Others     : ����,����16515083,����80020910
************************************************************************/

EINT32 GetDialerGrpNumberByAirID(EUINT32 uiAirGrpID)
{
    EUINT32 uiDialerGrpNum = 0;

    if( ETERROR == ConvertGroupIDToUserNumber(uiAirGrpID,0, &uiDialerGrpNum) )
    {
        uiDialerGrpNum = 0;
    }
    return uiDialerGrpNum;
}

void testIDConvert()
{
    EUINT32 uiID=16515073;
    EUINT32 uiUserNum;
    EUINT32 uigrpID=16515083;
    EUINT32 uigrpUserNum;
    int i=0;

    for(i=0;i<8;i++)
    {
    uiUserNum = GetDialerIndNumberByAirID(uiID+i);
    printf("ID=%u,UserNum=%u\n",uiID+i,uiUserNum);
    }

    uigrpUserNum = GetDialerGrpNumberByAirID(uigrpID);

    printf("grpID=%u,grpUserNum=%u\n",uigrpID,uigrpUserNum);

}
void teststring(char *p)
{
strcpy(p,"123456789");
printf("teststring=%s,strlen=%d,sizeof(p)=%d\n",p,strlen(p),sizeof(*p));
}

#define Min(a,b) (((a) > (b) )? (b) : (a))


CFG_TBL_INFO_T   g_tCfgTbl ;
PCFG_TBL_INFO_T  g_ptCfgTbl ;
CFG_PDC_LOCAL_MS_T   *gpatLocalMs[MAX_LOCAL_PREFIX_NUM];



EINT32 InitCfgTbl()
{
    memset(&g_tCfgTbl, 0, sizeof(g_tCfgTbl));
    return ETOK;
}

void testvoidpar(void *pvoidvalue)
{
     CFG_PDC_LOCAL_MS_T *pLocalMs=NULL;
     char *pchar =(char *)pvoidvalue;
     int *pint =(int *)pvoidvalue;
     short *pshort =(short *)pvoidvalue;

     printf("sizeof(*pvoidvalue) = %d.\n",sizeof(*pvoidvalue));
     pLocalMs=(CFG_PDC_LOCAL_MS_T *)pvoidvalue;

     printf("sizeof(*pLocalMs) = %d,strlen=%d.\n",
        sizeof(*pLocalMs),strlen(pLocalMs->strDialPrefix) );

     printf("sizeof(*pchar) =%d,sizeof(*pint) =%d,sizeof(*pshort) =%d.\n",
        sizeof(*pchar),sizeof(*pint),sizeof(*pshort));

     printf("sizeof(pchar) =%d,sizeof(pint) =%d,sizeof(pshort) =%d.\n",
        sizeof(pchar),sizeof(pint),sizeof(pshort));


}

void teststring1()
{
    char adial[16]={0};
    int a=0,b=0;
    EINT8 *pPrefixInTable = NULL;
    CFG_PDC_LOCAL_MS_T tLocalMs;
    CFG_PDC_LOCAL_MS_T *ptLocalMs =NULL;

    memset(&tLocalMs,0,sizeof(tLocalMs));

    memcpy(adial,"80020",16);
    teststring(adial);

    pPrefixInTable=adial;
    teststring(pPrefixInTable);
    printf("teststring=%s,%d\n",pPrefixInTable,strlen(pPrefixInTable));
    printf("Min(a:%d,b:%d):%d.\n",a,b,Min(a,b));
    a =2;b=5;
    printf("Min(a:%d,b:%d):%d.\n",a,b,Min(a,b));
        a =333;b=222;
    printf("Min(a:%d,b:%d):%d.\n",a,b,Min(a,b));
        a =999;b=999;
    printf("Min(a:%d,b:%d):%d.\n",a,b,Min(a,b));

    memcpy(tLocalMs.strDialPrefix,"571001",sizeof(tLocalMs.strDialPrefix));
    tLocalMs.uiFirstEcnid  = 111;
    tLocalMs.uiSecondEcnid = 222;
    testvoidpar((void *)&tLocalMs);
    printf("sizeof(tLocalMs)=%d,sizeof(*ptLocalMs)=%d\n"
        ,sizeof(tLocalMs),sizeof(*ptLocalMs));
}

void testCfgTbl()
{
    CFG_PDC_LOCAL_MS_T *pcfgLocalMs = NULL;

    printf("testCfgTbl\n");
    memcpy(g_tCfgTbl.atLocalMs[0].strDialPrefix,"5731",sizeof(g_tCfgTbl.atLocalMs[0].strDialPrefix));
    g_tCfgTbl.atLocalMs[0].uiFirstEcnid  = 111;
    g_tCfgTbl.atLocalMs[0].uiSecondEcnid = 222;
    printf("atLocalMs[0].strDialPrefix len =%d\n"
            ,strlen(g_tCfgTbl.atLocalMs[0].strDialPrefix));
    printf("atLocalMs[10].strDialPrefix len =%d\n"
            ,strlen(g_tCfgTbl.atLocalMs[10].strDialPrefix));
    pcfgLocalMs = &g_tCfgTbl.atLocalMs[0];

    printf("1pcfgLocalMs[%s] info,Ecnid1=%d,Ecnid2=%d.\n"
    ,pcfgLocalMs->strDialPrefix,pcfgLocalMs->uiFirstEcnid,pcfgLocalMs->uiSecondEcnid);

    //pcfgLocalMs = NULL;
    //pcfgLocalMs = &g_tCfgTbl.atLocalMs[10];
    //printf("2pcfgLocalMs[%s] info,Ecnid1=%d,Ecnid2=%d.\n"
    //,pcfgLocalMs->strDialPrefix,pcfgLocalMs->uiFirstEcnid,pcfgLocalMs->uiSecondEcnid);

    g_ptCfgTbl.patLocalMs[0] = pcfgLocalMs;

    printf("3pcfgLocalMs[%s] info,Ecnid1=%d,Ecnid2=%d,g_tCfgTbl=%d,%d,%d.\n"
    ,g_ptCfgTbl.patLocalMs[0]->strDialPrefix,g_ptCfgTbl.patLocalMs[0]->uiFirstEcnid,
    g_ptCfgTbl.patLocalMs[0]->uiSecondEcnid,sizeof(g_tCfgTbl),sizeof(g_ptCfgTbl),sizeof(gpatLocalMs));
}


#ifdef _DEBUG

void initEasttest_T()
{
    testIDConvert();
    teststring1();
    testCfgTbl();

}
#endif

