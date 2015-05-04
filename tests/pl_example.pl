MINIMIZE

W

SUBJECT TO

t_1 - W <= -1.000000
t_2 - W <= -10.000000
t_3 - W <= -5.000000

t_2 - t_1 - 17.000000 s_1_2 >= 18.000000
t_3 - t_1 - 17.000000 s_1_3 >= 18.000000
t_1 - t_2 - 17.000000 s_2_1 >= 27.000000
t_3 - t_2 - 17.000000 s_2_3 >= 27.000000
t_1 - t_3 - 17.000000 s_3_1 >= 22.000000
t_2 - t_3 - 17.000000 s_3_2 >= 22.000000

p_2 - p_1 - 2 ps_1_2 >= -1
p_3 - p_1 - 2 ps_1_3 >= -1
p_1 - p_2 - 2 ps_2_1 >= -1
p_3 - p_2 - 2 ps_2_3 >= -1
p_1 - p_3 - 2 ps_3_1 >= -1
p_2 - p_3 - 2 ps_3_2 >= -1

t_2 - t_1 - 17.000000 m_1_2 >= -17.000000
t_3 - t_1 - 17.000000 m_1_3 >= -17.000000
t_1 - t_2 - 17.000000 m_2_1 >= -17.000000
t_3 - t_2 - 17.000000 m_2_3 >= -17.000000
t_1 - t_3 - 17.000000 m_3_1 >= -17.000000
t_2 - t_3 - 17.000000 m_3_2 >= -17.000000

p_1 - 2 b_1 <= 1
p_2 - 2 b_2 <= 1
p_3 - 2 b_3 <= 1

p_1 - 2 b_1 >= 0
p_2 - 2 b_2 >= 0
p_3 - 2 b_3 >= 0

m_1_2 + m_2_1 >= 1
m_1_3 + m_3_1 >= 1
m_2_1 + m_1_2 >= 1
m_2_3 + m_3_2 >= 1
m_3_1 + m_1_3 >= 1
m_3_2 + m_2_3 >= 1

s_1_2 + s_2_1 + ps_1_2 + ps_2_1 >= 1
s_1_3 + s_3_1 + ps_1_3 + ps_3_1 >= 1
s_2_1 + s_1_2 + ps_2_1 + ps_1_2 >= 1
s_2_3 + s_3_2 + ps_2_3 + ps_3_2 >= 1
s_3_1 + s_1_3 + ps_3_1 + ps_1_3 >= 1
s_3_2 + s_2_3 + ps_3_2 + ps_2_3 >= 1

bb_1_2 - b_1 + b_2 <= 1
bb_1_3 - b_1 + b_3 <= 1
bb_2_1 - b_2 + b_1 <= 1
bb_2_3 - b_2 + b_3 <= 1
bb_3_1 - b_3 + b_1 <= 1
bb_3_2 - b_3 + b_2 <= 1

bb_1_2 - b_2 + b_1 <= 1
bb_1_3 - b_3 + b_1 <= 1
bb_2_1 - b_1 + b_2 <= 1
bb_2_3 - b_3 + b_2 <= 1
bb_3_1 - b_1 + b_3 <= 1
bb_3_2 - b_2 + b_3 <= 1

bb_1_2 - b_1 - b_2 >= -1
bb_1_3 - b_1 - b_3 >= -1
bb_2_1 - b_2 - b_1 >= -1
bb_2_3 - b_2 - b_3 >= -1
bb_3_1 - b_3 - b_1 >= -1
bb_3_2 - b_3 - b_2 >= -1

bb_1_2 + b_1 + b_2 >= 1
bb_1_3 + b_1 + b_3 >= 1
bb_2_1 + b_2 + b_1 >= 1
bb_2_3 + b_2 + b_3 >= 1
bb_3_1 + b_3 + b_1 >= 1
bb_3_2 + b_3 + b_2 >= 1

m_1_2 - c_1_2_2 + c_1_2_1 <= 1
m_1_3 - c_1_2_3 + c_1_2_1 <= 1
m_2_1 - c_1_2_1 + c_1_2_2 <= 1
m_2_3 - c_1_2_3 + c_1_2_2 <= 1
m_3_1 - c_1_2_1 + c_1_2_3 <= 1
m_3_2 - c_1_2_2 + c_1_2_3 <= 1
m_1_2 - c_1_3_2 + c_1_3_1 <= 1
m_1_3 - c_1_3_3 + c_1_3_1 <= 1
m_2_1 - c_1_3_1 + c_1_3_2 <= 1
m_2_3 - c_1_3_3 + c_1_3_2 <= 1
m_3_1 - c_1_3_1 + c_1_3_3 <= 1
m_3_2 - c_1_3_2 + c_1_3_3 <= 1

c_1_2_1 - s_1_1 <= 0
c_1_2_2 - s_1_2 <= 0
c_1_2_3 - s_1_3 <= 0
c_1_3_1 - s_1_1 <= 0
c_1_3_2 - s_1_2 <= 0
c_1_3_3 - s_1_3 <= 0

m_2_1 - c_1_2_1 <= 0
m_2_2 - c_1_2_2 <= 0
m_2_3 - c_1_2_3 <= 0
m_3_1 - c_1_3_1 <= 0
m_3_2 - c_1_3_2 <= 0
m_3_3 - c_1_3_3 <= 0

t_1 - t_2 <= -1.000000
t_1 - t_3 <= -1.000000

2 ps_1_2 + 2 ps_2_1 - p_1 + p_2 >= 0
2 ps_1_3 + 2 ps_3_1 - p_1 + p_3 >= 0
2 ps_2_1 + 2 ps_1_2 - p_2 + p_1 >= 0
2 ps_2_3 + 2 ps_3_2 - p_2 + p_3 >= 0
2 ps_3_1 + 2 ps_1_3 - p_3 + p_1 >= 0
2 ps_3_2 + 2 ps_2_3 - p_3 + p_2 >= 0

2 ps_1_2 + 2 ps_2_1 - p_2 + p_1 >= 0
2 ps_1_3 + 2 ps_3_1 - p_3 + p_1 >= 0
2 ps_2_1 + 2 ps_1_2 - p_1 + p_2 >= 0
2 ps_2_3 + 2 ps_3_2 - p_3 + p_2 >= 0
2 ps_3_1 + 2 ps_1_3 - p_1 + p_3 >= 0
2 ps_3_2 + 2 ps_2_3 - p_2 + p_3 >= 0

al_1_2_1 - bb_1_1 - m_1_1 + c_1_2_1 >= -1
al_1_3_1 - bb_1_1 - m_1_1 + c_1_3_1 >= -1
al_1_2_2 - bb_2_1 - m_1_2 + c_1_2_2 >= -1
al_1_3_2 - bb_2_1 - m_1_2 + c_1_3_2 >= -1
al_1_2_3 - bb_3_1 - m_1_3 + c_1_2_3 >= -1
al_1_3_3 - bb_3_1 - m_1_3 + c_1_3_3 >= -1

2 al_1_2_1 - bb_1_1 - m_1_1 + c_1_2_1 <= 0
2 al_1_3_1 - bb_1_1 - m_1_1 + c_1_3_1 <= 0
2 al_1_2_2 - bb_2_1 - m_1_2 + c_1_2_2 <= 0
2 al_1_3_2 - bb_2_1 - m_1_2 + c_1_3_2 <= 0
2 al_1_2_3 - bb_3_1 - m_1_3 + c_1_2_3 <= 0
2 al_1_3_3 - bb_3_1 - m_1_3 + c_1_3_3 <= 0

bet_1_2_1 - bb_1_2 - c_1_2_1 + s_2_1 >= -1
bet_1_3_1 - bb_1_3 - c_1_3_1 + s_3_1 >= -1
bet_1_2_2 - bb_2_2 - c_1_2_2 + s_2_2 >= -1
bet_1_3_2 - bb_2_3 - c_1_3_2 + s_3_2 >= -1
bet_1_2_3 - bb_3_2 - c_1_2_3 + s_2_3 >= -1
bet_1_3_3 - bb_3_3 - c_1_3_3 + s_3_3 >= -1

2 bet_1_2_1 - bb_1_2 - c_1_2_1 + s_2_1 <= 0
2 bet_1_3_1 - bb_1_3 - c_1_3_1 + s_3_1 <= 0
2 bet_1_2_2 - bb_2_2 - c_1_2_2 + s_2_2 <= 0
2 bet_1_3_2 - bb_2_3 - c_1_3_2 + s_3_2 <= 0
2 bet_1_2_3 - bb_3_2 - c_1_2_3 + s_2_3 <= 0
2 bet_1_3_3 - bb_3_3 - c_1_3_3 + s_3_3 <= 0

1.000000 b_1 <= 0.000000
1.000000 al_1_3_2 + 1.000000 bet_1_3_2 + 1.000000 b_2 <= 1.000000
1.000000 al_1_2_3 + 1.000000 bet_1_2_3 + 1.000000 b_3 <= 1.000000

BOUNDS

W >= 0

t_1 >= 0
t_2 >= 0
t_3 >= 0

1 <= p_1 <= 2
1 <= p_2 <= 2
1 <= p_3 <= 2

VARIABLES

W

t_1
t_2
t_3

p_1
p_2
p_3

s_1_1
s_1_2
s_1_3
s_2_1
s_2_2
s_2_3
s_3_1
s_3_2
s_3_3

ps_1_2
ps_1_3
ps_2_1
ps_2_3
ps_3_1
ps_3_2

m_1_1
m_1_2
m_1_3
m_2_1
m_2_2
m_2_3
m_3_1
m_3_2
m_3_3

c_1_2_1
c_1_3_1
c_1_2_2
c_1_3_2
c_1_2_3
c_1_3_3

bb_1_1
bb_1_2
bb_1_3
bb_2_1
bb_2_2
bb_2_3
bb_3_1
bb_3_2
bb_3_3

b_1
b_2
b_3

al_1_2_1
al_1_3_1
al_1_2_2
al_1_3_2
al_1_2_3
al_1_3_3

bet_1_2_1
bet_1_3_1
bet_1_2_2
bet_1_3_2
bet_1_2_3
bet_1_3_3

END
