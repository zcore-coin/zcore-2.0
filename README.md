<a href="https://aimeos.org/">
    <img src="https://zcore.cash/img/logogit.png" alt="ZCore logo" title="ZCore" align="right" />
</a>

ZCore (ZCR) integration/staging repository
======================
> Official Repository - PoS/MN

:star: ZCore is an experimental digital currency that enables anonymous, instant payments to anyone, anywhere in the world. ZCore uses peer-to-peer technology to operate with no central authority: managing transactions and issuing money are carried out collectively by the network. ZCore is the name of the open source software which enables the use of this currency.

<p align="center"><a href="https://github.com/zcore-coin/zcore-2.0/releases"><img src="https://zcore.cash/img/wallet.png" /></a></p>
<hr>

|Specifications		   		| 					  |						|					  |
|:-------------------- 		| :------------------ | :------------------ | :------------------ |
|Name  		                | `ZCore`             |Blocks per Day   	| `1440`              |
|Ticker 				    | `ZCR`               |Block Time  			| `1 MINUTE`          |
|Algorithm					| `Quark`             |Stake Min Age		| `2 HOURS`           |
|Type 						| `PoS/MN`            |Halving Block  		| `394200`            |
|Total Suply 			    | `18,000,000 ZCR`    |Port 			    | `17293`    		  |
|Masternode Collateral      | `5,000 ZCR`         |Datadir			    | `.zcr`			  |

<p align="center"><img src="https://zcore.cash/img/gitblocks.png" /></a></p>

ZCore 2.0 Swap Burn
======================
https://explorer.zcore.network/address/zUmK5U8barMnP34BZqGXjYLxjnfnRrePPe

ZCRT Swap Burn
======================
https://explorer.zcore.network/address/21XyrsZaosjrRmN8rQKy1pFSW9Zh7LrADjv

Add nodes
======================
```
# zcore.conf

addnode=104.238.133.126:17293
addnode=140.82.44.143:17293
addnode=104.238.134.207:17293
addnode=140.82.1.119:17293
addnode=45.32.249.115:17293
addnode=108.61.96.132:17293
addnode=45.32.139.101:17293
addnode=8.9.36.25:17293
```

Staking
======================
Enable
```
# zcore.conf
staking=1
```

Disable
```
# zcore.conf
staking=0
```

<h3>Licence</h3>
ZCore is released under the terms of the MIT license. See COPYING for more information or see https://opensource.org/licenses/MIT.
