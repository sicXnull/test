// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2019 The Redux Developers
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
    (     0, uint256("0x6b0516bfc0b5fd9949c2182b948075ade09fd6cc1a7e2622de221798d6bf2699"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1554522284, // * UNIX timestamp of last checkpoint block
    1456251,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1500        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x64aaa6dc4f520b42e36d3eb116847e8ccf216e0602f7a82c569564e14f358b63"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1554515599,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x6cd940c5863962bd22795d125ddb2fa7350db3d36736aa81e87902a6df092e43"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1554515619,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

libzerocoin::ZerocoinParams* CChainParams::OldZerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
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
        pchMessageStart[0] = 0x82;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xec;
        pchMessageStart[3] = 0xd7;
        vAlertPubKey = ParseHex("044d0db80b9e6137f4482f25c197a49c21470b21a842ac33184658daea0ee5817452d859140dce6dd3f45743b5b64893b1ad3a4ad4873b370e263e993dd6f51ccb");
        nDefaultPort = 16610;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Redux: 1 day
        nTargetSpacing = 1 * 60;  // Redux: 1 minute
        nMaturity = 50;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 30000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 400;

        nModifierUpdateBlock = 401;

        nZerocoinStartHeight = 401;

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
        const char* pszTimestamp = "Fox News - 4/5/2019 President Trump says new border wall looks great";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1554522284;
        genesis.nBits = 0x207fffff;;
        genesis.nNonce = 54323;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x6b0516bfc0b5fd9949c2182b948075ade09fd6cc1a7e2622de221798d6bf2699"));
        assert(genesis.hashMerkleRoot == uint256("0x8878060ae87427a950bb879455fba531ccb7ad48fed742a5e4e9971ac14ba0ba"));

        if(genesis.GetHash() != hashGenesisBlock)

        vSeeds.push_back(CDNSSeedData("0", "dns0.redux.io")); // run by Moonshot
        vSeeds.push_back(CDNSSeedData("1", "redux.seed.rho.industries")); // run by Julian Meyer (meyer9)

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 61);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x01)(0xbc).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "rx";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "03773902a4ee8f0827b9b89d483e3a7bdcb869dbcb19857283c3d47cc82b56e9ee";
        strObfuscationPoolDummyAddress = "ReCbXEEftGFHQ1ZCorDNBDphkk4EmQEgG7";

        /** Zerocoin */
        zerocoinModulus = "d9e855097e994b24ffa55d50c7bfeda97fb32a94d4e35011be94bd6e7ea930377af4fcc9f965c962e356dbf502b5d0d8cd"
             "8aeead175da5227a20a57c1e6803b25bcdf5a8788643af22653a82c86acfa5ad70a1d40a078868a090c199693599b0214ae5747c1079b62"
             "7fc8c514aba298ceaffe998cb58dad2d5c8ea384203e3d12393b4a625c876b9834ea57766dd347c86878268c96c8f986f4d88656a836d188"
             "6e35d768874919daddea7283b31f1e621975d3bb8714f8007211006d9c15fb890eed54d6bcafe243607e819009a820651f6494e15628ad29"
             "5e49657cb82903ec12a2096271bfe26c8f013d6674edba62bc400a67c89133a5f7f2a28004da83a11948213e725aba70e8aa9604ace06274"
             "a73c1ee6ea099ca1c4c06f8074fa79867bb84d32e5d80e453a60f5414fee670c9a89f3832ecca6c2b1524991c8f556bda4ac08a05ac45bd8"
             "667de0670e7a5bb34b72783a86294a7471842e8d7ef540f8f569a0a4285310e91ae291f208810bdaefbdfe46f21fc563b096d38057d9b5d";


        nZerocoinLastOldParams = 99999999; // Updated to defer zerocoin v2 for further testing.

        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
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
        pchMessageStart[0] = 0x36;
        pchMessageStart[1] = 0x65;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0x3b;
        vAlertPubKey = ParseHex("04f53099e956b685a3629a3e20e06c17db163ca2c6e94b7182740760c6c7c90f7dc28cecea8e30d7ed2cd908dc2a050cd0e0019abaf5db8cbfdb1d839f7c20e1f9");
        nDefaultPort = 16620;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Redux: 1 day
        nTargetSpacing = 1 * 10;  // Redux: 1 minute
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nLastPOWBlock = 400;
        nZerocoinStartHeight = 200;

        nZerocoinLastOldParams = 50000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1554515599;
        genesis.nNonce = 54328;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x64aaa6dc4f520b42e36d3eb116847e8ccf216e0602f7a82c569564e14f358b63"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 77); // Testnet redux addresses start with 'X' or 'Y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet redux script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet redux BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet redux BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet redux BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "tr";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "025b7ad3a3a6fd9cfa76634454708f684ac9aaea04ef22534802be63f3d5bc778c";
        strObfuscationPoolDummyAddress = "YKVnhohGpLNBgX1A58P2Gdg8DtY8NGXVNk";
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                     // here because we only have a 8 block finalization window on testnet
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
        pchMessageStart[0] = 0xb3;
        pchMessageStart[1] = 0xe8;
        pchMessageStart[2] = 0x6c;
        pchMessageStart[3] = 0xbe;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Redux: 1 day
        nTargetSpacing = 1 * 60;        // Redux: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1554515619;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 54327;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nZerocoinLastOldParams = 499;
        nZerocoinStartHeight = 100;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 16620;
        assert(hashGenesisBlock == uint256("0x6cd940c5863962bd22795d125ddb2fa7350db3d36736aa81e87902a6df092e43"));

        bech32_hrp = "reduxt";

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        nRequiredAccumulation = 1;

        // {
        //     "PrivateKey": "Y1EH53emUKQHVPhHvn3o6DG9itemMnvp1k",
        //     "PublicKey": "03ca5dccabd23b71482a1cf3d94ec491bc565720ff78b84cabf183f874fd1923b6"
        // }
        strSporkKey = "03ca5dccabd23b71482a1cf3d94ec491bc565720ff78b84cabf183f874fd1923b6";
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
        nDefaultPort = 16621;
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
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
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
