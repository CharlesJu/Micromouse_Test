typedef struct{
    float kP;   float kI;   float kD;
    float val;  float t;
    float e_prev;   float e_diff;
    float e_cur;    float e_tot;
    float o_min;    float o_max;
    float e_diff_prev;  short dT_cont;
     
} PID_Values;

class PID {
    public:
        PID(float kP, float kI, float kD){
            vals.kP = kP;   vals.kI = kI;   vals.kD = kD;
            vals.val = 0;   vals.t = 0;
            vals.e_prev = 0;    vals.e_diff = 0;
            vals.e_cur = 0;     vals.e_tot = 0;
            vals.o_min = -1E30; vals.o_max = 1E30;
            float e_diff_prev = 0;  short dT_cont = 0;
        }
        
        PID(float kP, float kI, float kD, float min, float max){
            vals.kP = kP;   vals.kI = kI;   vals.kD = kD;
            vals.val = 0;   vals.t = 0;
            vals.e_prev = 0;    vals.e_diff = 0;
            vals.e_cur = 0;     vals.e_tot = 0;
            vals.o_min = min;   vals.o_max = max;
            float e_diff_prev = 0;  short dT_cont = 0;
        }



        void update(float val, float t){
            //This needs to be update every loop
            vals.val = val;
            vals.t = t;
            if (t != vals.t){
                reset();
            } else {
                vals.e_cur = t - val;
                vals.e_diff = vals.e_prev - vals.e_cur;
                vals.e_tot += vals.e_cur;

                //Prevents I value Windup
                if((vals.e_diff < vals.e_diff_prev + 0.005 
                    || vals.e_diff > vals.e_diff_prev - 0.005)
                    && vals.dT_cont < 501) {
                    vals.dT_cont += 1;
                } else {
                    vals.dT_cont = 0;
                    vals.e_tot = 0;
                }
            }
        }

        void reset(){
            vals.val = 0;
            vals.e_prev = 0;    vals.e_diff = 0;
            vals.e_cur = 0;     vals.e_tot = 0;
        }

        float out(){
            float v = vals.e_cur * vals.kP + vals.e_tot * vals.kI + vals.e_diff * vals.kD;
        
            if(v < vals.o_min){
                v = vals.o_min;
            } else if (v > vals.o_max){
                v = vals.o_max;
            }
 
            vals.e_prev = vals.e_cur;
            
            return v;
        }

        float get(float val, float t){
            update(val, t);
            return out();
        }

        float getVal(){
            return vals.val;
        }

        float getErr(){
            return vals.e_cur;
        }

        float getPrevErr(){
            return vals.e_diff + vals.e_cur;
        }

        float getTotErr(){
            return vals.e_tot;
        }


    private:
        PID_Values vals;
};