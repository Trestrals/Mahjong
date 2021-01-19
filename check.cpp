<<<<<<< HEAD
#include"mahjong.h"
=======
#include "card.h"
#include "cardset.h"
>>>>>>> 上传最后成果
using std::sort;
using std::vector;
namespace cyc
{
<<<<<<< HEAD
	bool f[10][5][5][5][2],g[10][2];
	int pcnt[40];
	inline int min(const int &_a,const int &_b,const int &_c){int re=_a;_b<re?re=_b:0;_c<re?re=_c:0;return re;}
=======
        bool f[10][5][5][5][2],g[10][2];
        int pcnt[40];
        inline int min(const int &_a,const int &_b,const int &_c){int re=_a;_b<re?re=_b:0;_c<re?re=_c:0;return re;}
>>>>>>> 上传最后成果
}
using namespace cyc;
const bool cardset::check()const
{
<<<<<<< HEAD
	if((sum()-2)%3)return false;
	memset(pcnt,0,sizeof(pcnt));
	for(vector<card>::const_iterator i=cards.begin();i!=cards.end();++i)
		pcnt[i->get_type()]++;
	if(sum()==14)
	{
		bool ok=1;
		for(int i=1;i<=37;i%10==9?i+=2:++i)
			if(pcnt[i]&1)
			{
				ok=0;break;
			}
		if(ok)return true;//七对和了
	}
	g[0][0]=1;
	for(int i=1;i<=7;++i)
	{
		switch(pcnt[i+30])
		{
			case 0:case 3:g[i][0]=g[i-1][0],g[i][1]=g[i-1][1];break;
			case 1:return false;break;
			case 2:g[i][1]=g[i-1][0],g[i][0]=0;break;
			case 4:return false;
			default:puts("error");break;//出现问题了
		}
	}
	if(!(g[7][0]||g[7][1]))return false;//不可能
	memset(f,0,sizeof(f));f[0][0][0][0][0]=g[7][0],f[0][0][0][0][1]=g[7][1];
	//dp 万
	for(int i=1;i<=9;++i)
	{
		for(int j=0;j<=4;++j)
			for(int k=0;k<=4;++k)
				f[i][j][k][pcnt[i]][0]=f[i-1][0][j][k][0],
				f[i][j][k][pcnt[i]][1]=f[i-1][0][j][k][1];
		for(int j=4;j>=0;--j)
			for(int k=4;k>=0;--k)
				for(int o=pcnt[i];o>=0;--o)
				{
					for(int bit=0;bit<2;++bit)
					{
						if(!f[i][j][k][o][bit])continue;
						j&&k&&o?f[i][j-1][k-1][o-1][bit]=1:0,
						j>=3?f[i][j-3][k][o][bit]=1:0,
						k>=3?f[i][j][k-3][o][bit]=1:0,
						o>=3?f[i][j][k][o-3][bit]=1:0;
					}
					if(!f[i][j][k][o][0])continue;
					j>=2?f[i][j-2][k][o][1]=1:0,
					k>=2?f[i][j][k-2][o][1]=1:0,
					o>=2?f[i][j][k][o-2][1]=1:0;
				}
	}
	//dp 结束
	if(!(f[9][0][0][0][0]||f[9][0][0][0][1]))return false;//不可能
	f[0][0][0][0][0]=f[9][0][0][0][0],f[0][0][0][0][1]=f[9][0][0][0][1];
	memset(f+1,0,sizeof(f[0])*9);
	//dp 条
	for(int i=1;i<=9;++i)
	{
		for(int j=0;j<=4;++j)
			for(int k=0;k<=4;++k)
				f[i][j][k][pcnt[i+10]][0]=f[i-1][0][j][k][0],
				f[i][j][k][pcnt[i+10]][1]=f[i-1][0][j][k][1];
		for(int j=4;j>=0;--j)
			for(int k=4;k>=0;--k)
				for(int o=pcnt[i+10];o>=0;--o)
				{
					for(int bit=0;bit<2;++bit)
					{
						if(!f[i][j][k][o][bit])continue;
						i&&k&&o?f[i][j-1][k-1][o-1][bit]=1:0,
						j>=3?f[i][j-3][k][o][bit]=1:0,
						k>=3?f[i][j][k-3][o][bit]=1:0,
						o>=3?f[i][j][k][o-3][bit]=1:0;
					}
					if(!f[i][j][k][o][0])continue;
					j>=2?f[i][j-2][k][o][1]=1:0,
					k>=2?f[i][j][k-2][o][1]=1:0,
					o>=2?f[i][j][k][o-2][1]=1:0;
				}
	}
	//dp 结束
	if(!(f[9][0][0][0][0]||f[9][0][0][0][1]))return false;//不可能
	f[0][0][0][0][0]=f[9][0][0][0][0],f[0][0][0][0][1]=f[9][0][0][0][1];
	memset(f+1,0,sizeof(f[0])*9);
	//dp 筒
	for(int i=1;i<=9;++i)
	{
		for(int j=0;j<=4;++j)
			for(int k=0;k<=4;++k)
				f[i][j][k][pcnt[i+20]][0]=f[i-1][0][j][k][0],
				f[i][j][k][pcnt[i+20]][1]=f[i-1][0][j][k][1];
		for(int j=4;j>=0;--j)
			for(int k=4;k>=0;--k)
				for(int o=pcnt[i+20];o>=0;--o)
				{
					for(int bit=0;bit<2;++bit)
					{
						if(!f[i][j][k][o][bit])continue;
						j&&k&&o?f[i][j-1][k-1][o-1][bit]=1:0,
						j>=3?f[i][j-3][k][o][bit]=1:0,
						k>=3?f[i][j][k-3][o][bit]=1:0,
						o>=3?f[i][j][k][o-3][bit]=1:0;
					}
					if(!f[i][j][k][o][0])continue;
					j>=2?f[i][j-2][k][o][1]=1:0,
					k>=2?f[i][j][k-2][o][1]=1:0,
					o>=2?f[i][j][k][o-2][1]=1:0;
				}
	}
	//dp 结束
	return (f[9][0][0][0][1]);//返回结果
=======
        if((sum()-2)%3)return false;
        memset(pcnt,0,sizeof(pcnt));
        for(vector<card>::const_iterator i=cards->begin();i!=cards->end();++i)
                pcnt[i->get_type()]++;
        if(sum()==14)
        {
                bool ok=1;
                for(int i=1;i<=37;i%10==9?i+=2:++i)
                        if(pcnt[i]&1)
                        {
                                ok=0;break;
                        }
                if(ok)return true;//七对和了
        }
        g[0][0]=1;
        for(int i=1;i<=7;++i)
        {
                switch(pcnt[i+30])
                {
                        case 0:case 3:g[i][0]=g[i-1][0],g[i][1]=g[i-1][1];break;
                        case 1:return false;break;
                        case 2:g[i][1]=g[i-1][0],g[i][0]=0;break;
                        case 4:return false;
                        default:puts("error");break;//出现问题了
                }
        }
        if(!(g[7][0]||g[7][1]))return false;//不可能
        memset(f,0,sizeof(f));f[0][0][0][0][0]=g[7][0],f[0][0][0][0][1]=g[7][1];
        //dp 万
        for(int i=1;i<=9;++i)
        {
                for(int j=0;j<=4;++j)
                        for(int k=0;k<=4;++k)
                                f[i][j][k][pcnt[i]][0]=f[i-1][0][j][k][0],
                                f[i][j][k][pcnt[i]][1]=f[i-1][0][j][k][1];
                for(int j=4;j>=0;--j)
                        for(int k=4;k>=0;--k)
                                for(int o=pcnt[i];o>=0;--o)
                                {
                                        for(int bit=0;bit<2;++bit)
                                        {
                                                if(!f[i][j][k][o][bit])continue;
                                                j&&k&&o?f[i][j-1][k-1][o-1][bit]=1:0,
                                                j>=3?f[i][j-3][k][o][bit]=1:0,
                                                k>=3?f[i][j][k-3][o][bit]=1:0,
                                                o>=3?f[i][j][k][o-3][bit]=1:0;
                                        }
                                        if(!f[i][j][k][o][0])continue;
                                        j>=2?f[i][j-2][k][o][1]=1:0,
                                        k>=2?f[i][j][k-2][o][1]=1:0,
                                        o>=2?f[i][j][k][o-2][1]=1:0;
                                }
        }
        //dp 结束
        if(!(f[9][0][0][0][0]||f[9][0][0][0][1]))return false;//不可能
        f[0][0][0][0][0]=f[9][0][0][0][0],f[0][0][0][0][1]=f[9][0][0][0][1];
        memset(f+1,0,sizeof(f[0])*9);
        //dp 条
        for(int i=1;i<=9;++i)
        {
                for(int j=0;j<=4;++j)
                        for(int k=0;k<=4;++k)
                                f[i][j][k][pcnt[i+10]][0]=f[i-1][0][j][k][0],
                                f[i][j][k][pcnt[i+10]][1]=f[i-1][0][j][k][1];
                for(int j=4;j>=0;--j)
                        for(int k=4;k>=0;--k)
                                for(int o=pcnt[i+10];o>=0;--o)
                                {
                                        for(int bit=0;bit<2;++bit)
                                        {
                                                if(!f[i][j][k][o][bit])continue;
                                                i&&k&&o?f[i][j-1][k-1][o-1][bit]=1:0,
                                                j>=3?f[i][j-3][k][o][bit]=1:0,
                                                k>=3?f[i][j][k-3][o][bit]=1:0,
                                                o>=3?f[i][j][k][o-3][bit]=1:0;
                                        }
                                        if(!f[i][j][k][o][0])continue;
                                        j>=2?f[i][j-2][k][o][1]=1:0,
                                        k>=2?f[i][j][k-2][o][1]=1:0,
                                        o>=2?f[i][j][k][o-2][1]=1:0;
                                }
        }
        //dp 结束
        if(!(f[9][0][0][0][0]||f[9][0][0][0][1]))return false;//不可能
        f[0][0][0][0][0]=f[9][0][0][0][0],f[0][0][0][0][1]=f[9][0][0][0][1];
        memset(f+1,0,sizeof(f[0])*9);
        //dp 筒
        for(int i=1;i<=9;++i)
        {
                for(int j=0;j<=4;++j)
                        for(int k=0;k<=4;++k)
                                f[i][j][k][pcnt[i+20]][0]=f[i-1][0][j][k][0],
                                f[i][j][k][pcnt[i+20]][1]=f[i-1][0][j][k][1];
                for(int j=4;j>=0;--j)
                        for(int k=4;k>=0;--k)
                                for(int o=pcnt[i+20];o>=0;--o)
                                {
                                        for(int bit=0;bit<2;++bit)
                                        {
                                                if(!f[i][j][k][o][bit])continue;
                                                j&&k&&o?f[i][j-1][k-1][o-1][bit]=1:0,
                                                j>=3?f[i][j-3][k][o][bit]=1:0,
                                                k>=3?f[i][j][k-3][o][bit]=1:0,
                                                o>=3?f[i][j][k][o-3][bit]=1:0;
                                        }
                                        if(!f[i][j][k][o][0])continue;
                                        j>=2?f[i][j-2][k][o][1]=1:0,
                                        k>=2?f[i][j][k-2][o][1]=1:0,
                                        o>=2?f[i][j][k][o-2][1]=1:0;
                                }
        }
        //dp 结束
        return (f[9][0][0][0][1]);//返回结果
>>>>>>> 上传最后成果
}
