#include "ai.h"
#include "card.h"
#include "cardset.h"
namespace cyc//��������
{
    int pows(int a,int b)
    {
        int re=1;
        for(;b;b>>=1,a*=a)b&1?re*=a:0;
        return re;
    }
    int pow_4[5]={1,4,16,64,256};
    inline bool equal(const card &card1,const card &card2){return card1.get_type()==card2.get_type();}
    int c_cnttot[40],danger[40],c_cnthand[40],c_cntdust[40];
    bool vised[40];
    std::vector<card> tmpvec;
    std::vector<int> ret;
    inline int min(int a,int b,int c)
    {
        int re=a;
        b<re?re=b:0;
        c<re?re=c:0;
        return re;
    }
    inline int max(int a,int b){return a>b?a:b;}
    int cal_mark(int need,int leftcard)//�������Ƶĵ÷�
    {
        return 50*leftcard*leftcard/pow_4[need];
    }
    int cal_double()
    {
        int re=0;
        for(int i=1;i<=37;i%10==9?i+=2:++i)
            re+=c_cnthand[i]/2;
        return re;
    }
    inline int get_mark(int type)//����һ���Ƶĵ÷�
    {
        static const int danger_minus_base=20,card_base[5][5]={{0,0,0,0,0},
                                                                {0,500,100,0,-250},
                                                                {0,0,1500,1000,500},
                                                                {0,0,0,4000,3000},
                                                                {0,0,0,0,2500}},letter_base=100;//�ɵ�����
        if(type>=31&&type<=37)return card_base[c_cnthand[type]][c_cnttot[type]]-danger[type]/danger_minus_base-letter_base;
        else if(type%10&&type>0&&type<30)
        {
            int val=0;
            static const int mark_base1=500,mark_base2=100,mark_base3[5]={0,0,7,2,0};//�ɵ�����
            static const int mark_base4=50,mark_base5=5;
            if(type%10>2)
            {
                int min_num=min(c_cnthand[type-2],c_cnthand[type-1],c_cnthand[type]);
                val+=mark_base1*min_num,
                val-=mark_base2*min_num*mark_base3[c_cnthand[type]-min_num];
                val+=mark_base4*(c_cnthand[type-1]?1:0)*(4-c_cnttot[type-2]);
                val+=mark_base5*(4-c_cnttot[type-1])*(4-c_cnttot[type-2]);
            }
            if(type%10<8)
            {
                int min_num=min(c_cnthand[type+2],c_cnthand[type+1],c_cnthand[type]);
                val+=mark_base1*min_num,
                val-=mark_base2*min_num*mark_base3[c_cnthand[type]-min_num];
                val+=mark_base4*(c_cnthand[type+1]?1:0)*(4-c_cnttot[type+2]);
                val+=mark_base5*(4-c_cnttot[type+1])*(4-c_cnttot[type+2]);
            }
            if(type%10>1&&type%10<9)
            {
                int min_num=min(c_cnthand[type-1],c_cnthand[type+1],c_cnthand[type]);
                val+=mark_base1*min_num,
                val-=mark_base2*min_num*mark_base3[c_cnthand[type]-min_num];
                val+=mark_base4*(c_cnthand[type+1]?1:0)*(4-c_cnttot[type-1]);
                val+=mark_base5*(4-c_cnttot[type+1])*(4-c_cnttot[type-1]);
                val+=mark_base4*(c_cnthand[type-1]?1:0)*(4-c_cnttot[type+1]);
                val+=mark_base5*(4-c_cnttot[type-1])*(4-c_cnttot[type+1]);
            }
            val+=card_base[c_cnthand[type]][c_cnttot[type]];
            return val-danger[type]/danger_minus_base;
        }
        else return -2147483648;//����δ֪����
    }
    int trywin(const cardset &hand)//���غ�����Ҫ�Ľ��ţ��������>2�򷵻�3
    {
        //printf("try:");hand.print();
        if(hand.check())return 0;//����
        tmpvec=hand.get_cardset();
        cardset tmpcardset=hand;
        //��������
        for(int i=tmpvec.size()-1;i>=0;--i)
        {
            int itype=tmpvec[i].get_type();
            tmpcardset.del(itype);
            for(int j=1;j<=37;j%10==9?j+=2:++j)
                if(c_cnttot[j]<4&&itype!=j)
                {
                    tmpcardset.add(j);
                                    //printf("try replace %d with %d\n",itype,j);
                    if(tmpcardset.check())
                    {
                        //printf("change:");tmpcardset.print();
                        //printf("replace %d with %d and result is 1\n",itype,j);
                        return 1;
                    }
                    tmpcardset.del(j);
                }
            tmpcardset.add(itype);
        }
        //printf("change:"); tmpcardset.print();
        //û�����ƣ����ѻ��������ܺ�
        for(int i=tmpvec.size()-1;i>0;i--)
        {
            int tmptype1=tmpvec[i].get_type();
            tmpcardset.del(tmptype1);
            c_cnttot[tmptype1]--;
            for(int j=i-1;j>=0;j--)
            {
                int tmptype2=tmpvec[j].get_type();
                tmpcardset.del(tmptype2);
                c_cnttot[tmptype2]--;
                for(int t1=1;t1<=37;t1%10==9?t1+=2:++t1)
                    if(c_cnttot[t1]<4&&tmpvec[i].get_type()!=t1)
                    {
                        c_cnttot[t1]++;
                        tmpcardset.add(t1);
                        for(int t2=t1;t2<=37;t2%10==9?t2+=2:++t2)
                            if(c_cnttot[t2]<4&&tmpvec[j].get_type()!=t2)
                            {
                                tmpcardset.add(t2);
                                if(tmpcardset.check())
                                {
                                    //printf("change:");tmpcardset.print();
                                    //printf("replace %d with %d,%d with %d and result is 2\n",tmptype1,t1,tmptype2,t2);
                                    return 2;
                                }
                                tmpcardset.del(t2);
                            }
                        tmpcardset.del(t1);
                        c_cnttot[t1]--;
                    }
                tmpcardset.add(tmptype2);
                c_cnttot[tmptype2]++;
            }
            tmpcardset.add(tmptype1);
            c_cnttot[tmptype1]++;
        }
        return 3;
    }
    int trywin2(const cardset &hand)//���Ǽ��㻹δ����ʱһ������Ҫ���Ųź�
    {
        tmpvec=hand.get_cardset();
        cardset tmpcardset=hand;
        for(int i=1;i<=37;i%10==9?i+=2:++i)
        {
            if(c_cnttot[i]>3)continue;
            tmpcardset.add(i);
            if(tmpcardset.check())return 1;
            tmpcardset.del(i);
        }
        //puts("tmp:");
        //tmpcardset.print();
        for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        {
            int itype=i->get_type();
            tmpcardset.del(itype);
            for(int t1=1;t1<=37;t1%10==9?t1+=2:++t1)
                if(c_cnttot[t1]<4&&t1!=itype)
                {
                    ++c_cnttot[t1];
                    tmpcardset.add(t1);
                    for(int t2=t1;t2<=37;t2%10==9?t2+=2:++t2)
                        if(c_cnttot[t2]<4&&t2!=itype)
                        {
                            tmpcardset.add(t2);
                            if(tmpcardset.check())
                            {
                                //puts("tmp:");
                                //tmpcardset.print();
                                //printf("replace %d with %d %d\n",itype,t1,t2);
                                return 2;
                            }
                            tmpcardset.del(t2);
                        }
                    tmpcardset.del(t1);
                    --c_cnttot[t1];
                }
            tmpcardset.add(itype);
        }
        return 3;
    }
    inline bool can_eat1(int type){return (type%10>2&&c_cnthand[type-1]&&c_cnthand[type-2]);}
    inline bool can_eat2(int type){return(type%10>1&&type%10<9&&c_cnthand[type-1]&&c_cnthand[type+1]);}
    inline bool can_eat3(int type){return (type%10<8&&c_cnthand[type+1]&&c_cnthand[type+2]);}
    inline bool can_eat(int type)
    {
        if(type>30)return false;
        return can_eat1(type)||can_eat2(type)||can_eat3(type);
    }
}

using namespace cyc;

int AI_play(const cardset &hand,const cardset &bright,const cardset &dust,const cardset &odust,const int &leftcard)
//����ѡ����Ƶ�type ����Ѿ����Ʒ���-1��
//handΪ���ƣ�brightΪ���ϳ��ֹ����ƣ�dustΪ�������ƣ�odustΪ����������ƣ�leftcardΪ�ƶ�������
{
    printf("\n\n输出手牌：");
    hand.cprint();
    printf("输出结束\n");
    if(hand.check())return -1;
    //�������ֵ�����
    memset(c_cnttot,0,sizeof(c_cnttot));
    tmpvec=hand.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    tmpvec=bright.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    tmpvec=dust.get_cardset();
    //������ɣ���ʼ������ֵ��Ԥ����
    //��ʼ����ÿ���Ƶ�Σ�ն�
    tmpvec=odust.get_cardset();
    static const int danger_base1=1000,danger_base2=1500,danger_base3=250,danger_base4=1000;//�ɵ�����
    for(int i=1;i<=37;i%10==9?i+=2:++i)
        danger[i]=danger_base1*(4-c_cnttot[i]);
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        danger[i->get_type()]-=danger_base2;
    for(int a=1,b=2,c=8,d=9;a<30;a+=10,b+=10,c+=10,d+=10)
        danger[a]-=danger_base3*2,danger[b]-=danger_base3,danger[c]-=danger_base3,danger[d]-=danger_base3*2;
    for(int i=31;i<=37;++i)
        danger[i]-=danger_base4;
    //�������
    int need=trywin(hand);//���������Ҫ�Ľ���
    int mark_hand=cal_mark(need,leftcard);//�������Ƶ÷�
                                        //printf("��Ҫ%d���Ʋ��ܺ� �÷֣�%d\n",need,mark_hand);
    static const int markgate=1250;//�ɵ�����
                                        //goto test_point;//testing
    if(mark_hand<markgate)//�������ͣ�ѡ�����
    {
                                        //puts("AI ѡ�����");
        tmpvec=hand.get_cardset();
        int ansdanger=2147483647;
        memset(vised,0,sizeof(vised));
        ret.clear();
        for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        {
            int itype=i->get_type();
            if(vised[itype])continue;
                                        //printf("danger %d = %d\n",itype,danger[itype]);
            vised[itype]=1;
            if(danger[itype]<ansdanger)
            {
                ret.clear();ret.push_back(itype),ansdanger=danger[itype];
            }
            else if(danger[itype]==ansdanger)ret.push_back(itype);
        }
        return ret[rand()%ret.size()];
    }
    else//�����ϸߣ����Խ���
    {
                                        //test_point:;//testing
                                            //puts("AI ѡ�����");
        tmpvec=hand.get_cardset();
        memset(c_cnthand,0,sizeof(c_cnthand));
        for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
            ++c_cnthand[i->get_type()];
        tmpvec=dust.get_cardset();
        memset(c_cntdust,0,sizeof(c_cntdust));
        for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
            ++c_cntdust[i->get_type()];
        int double_num=cal_double();
        if(tmpvec.size()==14&&need>1&&double_num>=5)//���߶�
        {
            tmpvec=hand.get_cardset();
            int ansval=2147483647;
            ret.clear();
            for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
            {
                if(c_cnthand[i->get_type()]%2)
                {
                    int itype=i->get_type();
                    static const int double_base1[4]={500,50,5,0},double_base2=10;//�ɵ�����
                    int val1=(4-c_cnttot[itype])*double_base1[c_cntdust[itype]];
                    int val2=val1-danger[itype]/double_base2;
                                        //printf("type %d get mark %d danger %d\n",itype,val2,danger[itype]);//testing
                    if(val2<ansval)
                    {
                        ansval=val2;
                        ret.clear();
                        ret.push_back(itype);
                    }
                    else if(val2==ansval)
                    {
                        ret.push_back(itype);
                    }
                }
            }
            return ret[rand()%ret.size()];
        }
                                        //need=3;//testing
        static const int dust_base[4]={1,10,20,50};//�ɵ��������ͷ�������������ֻ�������ķ���
        switch(need)
        {
            case 1://����ƻ���һ��
            {
                cardset tmpcardset=hand;
                ret.clear();
                int ansval=-2147483648;
                for(int i=1;i<=37;i%10==9?i+=2:++i)
                {
                    if(c_cnthand[i])
                    {
                        --c_cnthand[i];
                        tmpcardset.del(i);
                        static const int danger_base=10,val_base[5]={0,1500,2500,3250,3750};//�ɵ�����
                        int val=danger[i]/danger_base;
                        for(int j=1;j<37;j%10==9?j+=2:++j)
                        {
                            if(i==j||c_cnttot[j]>=4)continue;
                            tmpcardset.add(j);
                            if(tmpcardset.check())
                                val+=val_base[4-c_cnttot[j]]/dust_base[c_cntdust[j]];
                            tmpcardset.del(j);
                        }
                        tmpcardset.add(i);
                        ++c_cnthand[i];
                        if(val>ansval)
                        {
                            ansval=val,ret.clear(),ret.push_back(i);
                        }
                        else if(val==ansval)
                            ret.push_back(i);
                    }
                }
                return ret[rand()%ret.size()];
                break;
            }
            case 2://����ƻ�������
            {
                cardset tmpcardset=hand;
                ret.clear();
                int ansval=-2147483648;
                for(int i=1;i<=37;i%10==9?i+=2:++i)
                    if(c_cnthand[i])
                    {
                        --c_cnthand[i],
                        tmpcardset.del(i);
                        static const int danger_base=10;//�ɵ�����
                        int val=danger[i]/danger_base;
                        for(int j=1;j<=37;j%10==9?j+=2:++j)
                            if(c_cnthand[j])
                            {
                                --c_cnthand[j],
                                tmpcardset.del(j);
                                for(int t1=1;t1<=37;t1%10==9?t1+=2:++t1)
                                    if(c_cnttot[t1]<4)
                                    {
                                        ++c_cnttot[t1],
                                        tmpcardset.add(t1);
                                        for(int t2=t1;t2<=37;t2%10==9?t2+=2:++t2)
                                            if(c_cnttot[t2]<4)
                                            {
                                                ++c_cnttot[t2],
                                                tmpcardset.add(t2);
                                                if(tmpcardset.check())
                                                {
                                                                    //printf("replace %d %d with %d %d\n",i,j,t1,t2);
                                                    static const int val_base[4][4]={{300,450,550,600},
                                                                                     {450,600,700,750},
                                                                                     {550,700,800,850},
                                                                                     {600,750,850,900}},
                                                                     val_same_base[4]={25,40,50,55};
                                                    if(t1==t2)val+=val_same_base[4-c_cnttot[t1]]/dust_base[c_cntdust[t1]];
                                                    val+=val_base[4-c_cnttot[t1]][4-c_cnttot[t2]]/dust_base[max(c_cntdust[t1],c_cntdust[t2])];
                                                }
                                                tmpcardset.del(t2),
                                                --c_cnttot[t2];
                                            }
                                        tmpcardset.del(t1),
                                        --c_cnttot[t1];
                                    }
                                tmpcardset.add(j),
                                ++c_cnthand[j];
                            }
                        tmpcardset.add(i),
                        ++c_cnthand[i];
                                            //printf("val %d = %d\n",i,val);
                        if(val>ansval)
                        {
                            ansval=val,ret.clear(),ret.push_back(i);
                        }
                        else if(val==ansval)
                            ret.push_back(i);
                    }
                return ret[rand()%ret.size()];
                break;
            }
            case 3://����ƻ�������
            {
                tmpvec=hand.get_cardset();
                ret.clear();
                int ansmark=2147483647;
                memset(vised,0,sizeof(vised));
                for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
                {
                    int itype=i->get_type();
                    if(vised[itype])continue;
                    int mark=get_mark(itype);
                    vised[itype]=1;
                                            //printf("type %d get mark %d danger %d\n",itype,mark,danger[itype]);//testing
                    if(mark<ansmark)
                    {
                        ret.clear(),ansmark=mark,ret.push_back(itype);
                    }
                    else if(mark==ansmark)
                        ret.push_back(itype);
                }
                return ret[rand()%ret.size()];
                break;
            }
            default:;//����δ֪����
        }
    }
    return -1;
}
bool AI_crash(int type,const cardset &hand,const cardset &bright,const int &leftcard)
//�����Ƿ���type�Ʋ���
//handΪ���ƣ�brightΪ������������(������type����leftcardΪ�ƶ�������
{
    //�������ֵ�����
    memset(c_cnttot,0,sizeof(c_cnttot));
    tmpvec=hand.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    if(c_cnttot[type]<2)return false;//��������˵�Ȼ����
    tmpvec=bright.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    //�������
    int need=trywin2(hand);//���������Ҫ�Ľ���
    int mark=cal_mark(need,leftcard);//�������Ƶ÷�
    static const int markgate=1250;//�ɵ�����
    if(mark<markgate)//�������ͣ�ѡ�����
        return 0;//���ز���
    tmpvec=hand.get_cardset();
    memset(c_cnthand,0,sizeof(c_cnthand));
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        ++c_cnthand[i->get_type()];
    int double_num=cal_double();
                        //printf("need:%d cnt%d:%d\n",need,type,c_cnthand[type]);
    if(need>=3&&c_cnthand[type]==2)return true;//��������Զ���Ҹպ���������ѡ����
    cardset tmpcardset=hand;
    tmpcardset.del(type),tmpcardset.del(type);
    if(trywin(tmpcardset)<need)return true;//������������棬��ѡ����
    else return false;//������
    return false;//����δ֪���󣬲���
}
/*bool AI_dark_gang(int type,const cardset &hand,const cardset &bright,const int &leftcard)
//�����Ƿ񰵸�type�Ʋ�����������Ӧǡ����3��type�ƣ�
//handΪ���ƣ�brightΪ������������(������type����leftcardΪ�ƶ�������
{
    //�������ֵ�����
    memset(c_cnttot,0,sizeof(c_cnttot));
    tmpvec=hand.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    if(c_cnttot[type]!=3)return false;//����ܲ��˵�Ȼ����
    tmpvec=bright.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    //�������
    int need=trywin2(hand);//���������Ҫ�Ľ���
    int mark=cal_mark(need,leftcard);//�������Ƶ÷�
    static const int markgate=1250;//�ɵ�����
    if(mark<markgate)//�������ͣ�ѡ�����
        return 0;//���ز���
    tmpvec=hand.get_cardset();
    memset(c_cnthand,0,sizeof(c_cnthand));
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        ++c_cnthand[i->get_type()];
    int double_num=cal_double();
    if(tmpvec.size()==14&&need>1&&double_num>=5)//���߶�
        return false;//�߶Բ���
    cardset tmpcardset=hand;
    tmpcardset.del(type),tmpcardset.del(type),tmpcardset.del(type);
    if(trywin2(tmpcardset)>need)return false;//����ܺ󷴶��Կ����򲻸�
    else return true;//����Ӹ�����һ��
    return false;//����δ֪���󣬲���
}
//�������������棬AIѡ�񲻸�
bool AI_add_gang(int type,const cardset &hand,const cardset &bright,const int &leftcard)
//�����Ƿ�Ӹ�type�Ʋ�������������Ӧǡ��type�Ŀ��ӣ��˴������жϣ�
//handΪ���ƣ�brightΪ������������(������type����leftcardΪ�ƶ�������
{
    //�������ֵ�����
    memset(c_cnttot,0,sizeof(c_cnttot));
    tmpvec=hand.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    if(c_cnttot[type]!=3)return false;//����ܲ��˵�Ȼ����
    tmpvec=bright.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    //�������
    int need=trywin2(hand);//���������Ҫ�Ľ���
    int mark=cal_mark(need,leftcard);//�������Ƶ÷�
    static const int markgate=1250;//�ɵ�����
    if(mark<markgate)//�������ͣ�ѡ�����
        return 0;//���ز���
    cardset tmpcardset=hand;
    tmpcardset.add(type);
    if(trywin(tmpcardset)<need)return false;//���������Ϊ����������󣬲��粻��
    else return true;//����ܺ�����һ��
    return false;//����δ֪���󣬲���
}*/
int AI_eat(int type,const cardset &hand,const cardset &bright,const int &leftcard)
//�����Ƿ��type�Ʋ�����1Ϊ��ǰ���ţ�2Ϊ��ǰ���һ�ţ�3Ϊ�Ժ����ţ�0Ϊ����
//handΪ���ƣ�brightΪ������������(������type����leftcardΪ�ƶ�������
{
    //�������ֵ�����
    memset(c_cnttot,0,sizeof(c_cnttot));
    tmpvec=hand.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    memcpy(c_cnthand,c_cnttot,sizeof(c_cnthand));
    if(!can_eat(type))return false;//����Բ��˵�Ȼ����
    tmpvec=bright.get_cardset();
    for(std::vector<card>::iterator i=tmpvec.begin();i!=tmpvec.end();++i)
        c_cnttot[i->get_type()]++;
    //�������
    int need=trywin2(hand);//���������Ҫ�Ľ���
    int mark=cal_mark(need,leftcard);//�������Ƶ÷�
    static const int markgate=1250;//�ɵ�����
    if(mark<markgate)//�������ͣ�ѡ�����
        return 0;//���ز���
    ret.clear();
    cardset tmpcardset=hand;
    bool better=0;
    if(can_eat1(type))
    {
        tmpcardset.del(type-1),tmpcardset.del(type-2);
        if(need==3)//���ƽ�Զ
        {
            if(trywin(tmpcardset)<need)//������ߣ����ǳ�
            {
                if(!better){ret.clear(),better=1,ret.push_back(1);}
                else ret.push_back(1);
            }
            else if(!better)//ûɶ���棬���ų�
                ret.push_back(1);

        }
        else
            if(trywin(tmpcardset)<need)ret.push_back(1);//���������ǳ�
        tmpcardset.add(type-1),tmpcardset.add(type-2);
    }
    if(can_eat2(type))
    {
        tmpcardset.del(type-1),tmpcardset.del(type+1);
        if(need==3)//���ƽ�Զ
        {
            if(trywin(tmpcardset)<need)//������ߣ����ǳ�
            {
                if(!better){ret.clear(),better=1,ret.push_back(2);}
                else ret.push_back(2);
            }
            else if(!better)//ûɶ���棬���ų�
                ret.push_back(2);
        }
        else
            if(trywin(tmpcardset)<need)ret.push_back(2);//���������ǳ�
        tmpcardset.add(type-1),tmpcardset.add(type-2);
    }
    if(can_eat3(type))
    {
        tmpcardset.del(type+1),tmpcardset.del(type+2);
        if(need==3)//���ƽ�Զ
        {
            if(trywin(tmpcardset)<need)//������ߣ����ǳ�
            {
                if(!better){ret.clear(),better=1,ret.push_back(3);}
                else ret.push_back(3);
            }
            else if(!better)//ûɶ���棬���ų�
                ret.push_back(3);

        }
        else
            if(trywin(tmpcardset)<need)ret.push_back(3);//���������ǳ�
        tmpcardset.add(type+1),tmpcardset.add(type+2);
    }
    if(ret.empty())return 0;//û��ѡ���
    return ret[rand()%ret.size()];
}
