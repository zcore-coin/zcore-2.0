// Copyright (c) 2018-2019 The ZCore developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <masternode-devbudget.h>

CDevBudget devbudget;

void CDevBudget::PrepareBudget() {
    CBitcoinAddress address = CBitcoinAddress(Params().DevRewardAddress());
    payee = GetScriptForDestination(address.Get());

    LogPrintf("CDevBudget::PrepareBudget(): %s\n", address.ToString());
}

bool CDevBudget::IsTransactionValid(const CTransaction& txNew, int nBlockHeight)
{
    PrepareBudget();

    CBlockIndex* pindexPrev = chainActive.Tip();
    if (!pindexPrev){
        return false;
    }

    if(txNew.IsZerocoinSpend()){
        return true;
    }

    CAmount budgetPayment = GetDevelopersPayment(nBlockHeight);

    bool found = false;
    int i = 0;
    if(budgetPayment > 0){
        BOOST_FOREACH (CTxOut out, txNew.vout) {
            if (payee == out.scriptPubKey) {
                if (i > 0 && out.nValue >= budgetPayment) {
                    found = true;
                }
                else{
                    LogPrintf("CDevBudget::IsTransactionValid - Found valid Dev Budget address, but wrong amount %d\n", out.nValue);
                }
            }
            i++;
        }
    }
    else{
        LogPrintf("CDevBudget::IsTransactionValid - Skipping validate devbudget, because is 0\n");
        found = true;
    }

    if (!found) {
        LogPrintf("CDevBudget::IsTransactionValid - Missing required payment %d for block %d\n", budgetPayment, nBlockHeight);
    }

    return found;
}

void CDevBudget::FillBlockPayee(CMutableTransaction& txNew, int64_t nFees, bool fProofOfStake)
{
    LogPrintf("Entered in CDevBudget::FillBlockPayee\n");

    CBlockIndex* pindexPrev = chainActive.Tip();
    if (!pindexPrev){
        return;
    }

    PrepareBudget();

    unsigned int i = txNew.vout.size();

    if(fProofOfStake && i > 1 && txNew.vout[1].IsZerocoinMint()){
        return;
    }

    if (txNew.vout[i - 1].nValue > 0) {
        CAmount budgetPayment = GetDevelopersPayment(pindexPrev->nHeight);

        if(budgetPayment > 0) {
            txNew.vout.resize(i + 1);
            txNew.vout[i].scriptPubKey = payee;
            txNew.vout[i].nValue = budgetPayment;

            //subtract budget payment from mn reward
            txNew.vout[i - 1].nValue -= budgetPayment;

            LogPrintf("Dev budget payment of %s to %s\n", FormatMoney(budgetPayment).c_str(), Params().DevRewardAddress().c_str());
        }
        else{
            LogPrintf("Dev budget payment equals 0\n");
        }
    }
    else{
        LogPrintf("Can't insert dev budget payment: vout value equals 0\n");
    }
}