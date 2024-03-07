/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Header file for the Public Subscribe System,
 * with the structures and function prototypes
 *
 ***************************************************************
 */

#ifndef pss_h
#define pss_h
#define MG 64

struct Info {
    int iId;
    int itm;
    int igp[MG];
    struct Info *iprev;
    struct Info *inext;
};
struct Subscription {
    int sId;
    struct Subscription *snext;
};
struct Group {
    int gId;
    struct Subscription *ggsub;
    struct Info *gfirst;
    struct Info *glast;
};
struct SubInfo {
    int sId;
    int stm;
    struct Info *sgp[MG];
    struct SubInfo *snext;
};

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(void);

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(struct Group g[64],struct SubInfo **temp);

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(struct Group G[64], int iTM,int iId,int* gids_arr,int size_of_gids_arr);

/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(struct Group G[64],struct SubInfo** head,int sTM,int sId,int* gids_arr,int size_of_gids_arr);

/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(struct Group G[64],struct SubInfo **head,int sId);

/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(struct Group G[64],struct SubInfo **head,int sId);

/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(struct Group G[64],struct SubInfo *head);

#endif /* pss_h */

