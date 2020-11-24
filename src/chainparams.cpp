// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The ZCore developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("695b79c8c234b45b2eeb4722f33373e471c9b686ff78efeb39da95f824a9f81b"))
    (5000, uint256("c5d5ef6903b40c642216814363a789cbd06f8132fac0b41a7dd0e10e6f002b56"))
    (9000, uint256("89f9dae0eebb52b2b0a0b891d21e31f36d5a5dcf392b04b97b17465980913680"))
    (20000, uint256("9bab5e8d61edc14511fde8f73df844026dca35c761ee06c68b6e7bd3dd314789"))
    (30000, uint256("254ed8dbecf44e0c985e79de0f6b81d45f77ed5ac9bbe0081f6c79f237cb2bb2"))
    (100000, uint256("74af0bda9e6c0a01d9a489dbe214319872eb7f6fbab3e0f86937822ff81c2264"))
    (200000, uint256("cf50c0a6fede1504ffdf3cd4b67923f088923aba3fe569783d57314da3db0f80"))
    (300000, uint256("6b3999126c9283ca95a83ba45536f5407f43942036c908a69751969bf2dba15c"))
    (400000, uint256("01d996a1d025bd9b7aea0b1470801b5e91e3551e5e48e25313946e1907008f00"))
    (500000, uint256("d886cfeaab38868fd813425f12f821a516b946543e8280c09db74c859d4f9699"))
    (550000, uint256("ccc54c0b128e8cc87f250fe8c8ee93e94bd2761ae624f6c8032cad4fdc588a35"))
    (578540,uint256("9fd51a2ea643d81d7d51bce9af1533d541a18c2cf311a17649e85c6d60b647c0"))
    (600000,uint256("88af7f2f5979e3a5f2193733e7a055de674c383e6d1561b570dd609b973cf05d"))
    (628020,uint256("d4ed80f276f8a2f1e27f137b493614502fb38527ac17fd7dfe6ee77eff8b3214"));
    
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1606235129, // * UNIX timestamp of last checkpoint block
    1411683,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("674cf2a0b8b7e31f0f04174176a5d7479e611c62bff5e829cdb4d70dde5def12"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1568075189,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("42be3f7d6910b2e55d6791ce563d4fa6f5fb80d0eb0c7775be5cb81149c316ce"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1568075518,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xCC;
        pchMessageStart[1] = 0x64;
        pchMessageStart[2] = 0x5C;
        pchMessageStart[3] = 0x66;
        vAlertPubKey = ParseHex("69715360d8d69a0178f10936a5ac3c6a6aa2235e229a9c22456bbc4acbd4d1d30a5f78dda20918dd11ca4d8b37a29b689467529d81b6bdbe601412ac9038518a48");
        nDefaultPort = 17293;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // ZCore starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetSpacing = 2 * 60;  // ZCR: 1 minutes
        nMaturity = 100;
        nMaxMoneyOut = 18000000 * COIN;

        nSubsidyHalvingBlock = 394200;
        nMasternodeCollateral = 5000;
        strDevFeeAddress = "zS44nzYNkZUWfV1TVVgUqJTeHqSjuPjbsi";

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 0;
        nZerocoinStartHeight = 0;
        nZerocoinStartTime = 1547096400; // Genesis time
        nBlockZerocoinV2 = 20;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "ZCore Genesis Block mined by Mosqueiro";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
        genesis.nTime = 1568072631;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 22464490;

        hashGenesisBlock = genesis.GetHash();
        //printf("Genesis mainnet - %s\n",hashGenesisBlock.ToString().c_str());
        //printf("Merkle mainnet - %s\n",genesis.hashMerkleRoot.ToString().c_str());
        assert(hashGenesisBlock == uint256("0x695b79c8c234b45b2eeb4722f33373e471c9b686ff78efeb39da95f824a9f81b"));
        assert(genesis.hashMerkleRoot == uint256("0x10d626f17c09ea9aba957a3308a1752a7159aafb8e029502dbcf937ee9e14a23"));

        vSeeds.push_back(CDNSSeedData("seed1.zcore.network", "seed1.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed2.zcore.network", "seed2.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed3.zcore.network", "seed3.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed4.zcore.network", "seed4.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed5.zcore.network", "seed5.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed6.zcore.network", "seed6.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed7.zcore.network", "seed7.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed8.zcore.network", "seed8.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed9.zcore.network", "seed9.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed10.zcore.network", "seed10.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed11.zcore.network", "seed11.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed12.zcore.network", "seed12.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed13.zcore.network", "seed13.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed14.zcore.network", "seed14.zcore.network"));
        vSeeds.push_back(CDNSSeedData("seed15.zcore.network", "seed15.zcore.network"));

        // ZCore addresses start with 'z'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 142);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 145);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 80);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0xB2)(0x47)(0x46).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0xB2)(0x43)(0x08).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x01)(0xac).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04be77009cadbebe92e46c074050f59e72c8dd5afed5691082d51276669dc29cf0859eacb4f843f2715bc31789b358dfafc237489114603e9c9eeb283b3c29b7f7";
        strObfuscationPoolDummyAddress = "zUADJmKffxr3cWKGiS25HsTPSv1cqHSteH";
        nStartMasternodePayments = 1547119800; // historical param

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zzcr to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xCB;
        pchMessageStart[1] = 0x61;
        pchMessageStart[2] = 0x85;
        pchMessageStart[3] = 0x50;
        vAlertPubKey = ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = 27293;
        nMinerThreads = 0;
        nTargetSpacing = 2 * 60;
        nLastPOWBlock = 200;
        nMaturity = 15;
        nModifierUpdateBlock = 0;
        nMaxMoneyOut = 18000000 * COIN;
        nZerocoinStartHeight = 15;
        nZerocoinStartTime = 1547096400;
        nBlockZerocoinV2 = 15;

        nSubsidyHalvingBlock = 1600;
        nMasternodeCollateral = 1000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1568075189;
        genesis.nNonce = 22382441;

        hashGenesisBlock = genesis.GetHash();

        //printf("Genesis testnet - %s\n",hashGenesisBlock.ToString().c_str());
        //printf("Merkle testnet - %s\n",genesis.hashMerkleRoot.ToString().c_str());

        assert(hashGenesisBlock == uint256("0x674cf2a0b8b7e31f0f04174176a5d7479e611c62bff5e829cdb4d70dde5def12"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet zcore addresses start with 'z' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet zcore script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04c1e97f69833b79eea380876d7210967148faa2315efe6f1427d1ea252b9941568f6a00d483e4c717cc73f1d2647a526523cc972776d76605ae34743913330fc9";
        strObfuscationPoolDummyAddress = "zLPK599pTL3YyiKxaPPsmWrSnSvNns8fJV";
        nStartMasternodePayments = 1547119740 + 500 * 120;
        nBudget_Fee_Confirmations = 3;

    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x31;
        pchMessageStart[1] = 0x45;
        pchMessageStart[2] = 0x27;
        pchMessageStart[3] = 0xA9;
        nMinerThreads = 1;
        nTargetSpacing = 2 * 60;
        nDefaultPort = 37293;

        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1568075518;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 22524360;

        hashGenesisBlock = genesis.GetHash();

        //printf("Genesis RegTest - %s\n",hashGenesisBlock.ToString().c_str());
        //printf("Merkle RegTest - %s\n",genesis.hashMerkleRoot.ToString().c_str());

        assert(hashGenesisBlock == uint256("0x42be3f7d6910b2e55d6791ce563d4fa6f5fb80d0eb0c7775be5cb81149c316ce"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 49293;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingBlock(int anSubsidyHalvingBlock) { nSubsidyHalvingBlock = anSubsidyHalvingBlock; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
