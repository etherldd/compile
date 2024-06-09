#ifndef IR_GENE_H
#define IR_GENE_H

#include "IR_list.h"
#include "stree.h"
#include "list.h"
#include "util.h"
#include "structList.h"

void IR_Exp(Snode* n, Operand catch);
void IR_CompSt(Snode* node);
IR_LIST* IR_content;

unsigned int globalCounter_t;
char* IR_geneTMP_t_str() {
    char* ret = (char*)malloc(sizeof(char) * 10);
    sprintf(ret, "t%d", globalCounter_t);
    globalCounter_t++;
    return ret;
}

Operand IR_geneTMP_t() {
    Operand cur_val = ir_Operand_init(IR_VARIABLE, IR_geneTMP_t_str());
    return cur_val;
}


unsigned int globalCounter_v;
char* IR_geneTMP_v_str() {
    char* ret = (char*)malloc(sizeof(char) * 10);
    sprintf(ret, "v%d", globalCounter_v);
    globalCounter_v++;
    return ret;
}
Operand IR_geneTMP_v() {
    Operand cur_val = ir_Operand_init(IR_VARIABLE, IR_geneTMP_v_str());
    return cur_val;
}

void IR_Args(Snode* n, Operand** tmps, int cur, int* length) {
    //Exp COMMA Args | Exp
    if (n->childs_num == 1) {
        *length = (cur + 1);
        *tmps = (Operand*)malloc(sizeof(Operand) * (cur + 1));
        (*tmps)[cur] = IR_geneTMP_t();
        IR_Exp(n->childs[0], (*tmps)[cur]);
    } else {
        IR_Args(n->childs[2], tmps, cur + 1, length);
        (*tmps)[cur] = IR_geneTMP_t();
        IR_Exp(n->childs[0], (*tmps)[cur]);
    }
}



void IR_Cond(Snode* n, Operand label_true, Operand label_false) {
    if (n->childs_num == 1) {
        //other cases
        Operand t1 = IR_geneTMP_t();
        Operand zero = ir_Operand_init(IR_CONSTANT, "0");
        IR_Exp(n, t1);
        //[IF t1 != #0 GOTO label_true]
        IR* cur_val_ir = (IR*)malloc(sizeof(IR));
        cur_val_ir->code_kind = IR_IF;
        cur_val_ir->u.if_st.op1 = t1;
        cur_val_ir->u.if_st.op2 = zero;
        cur_val_ir->u.if_st.op = "!=";
        cur_val_ir->u.if_st.desti = label_true;
        ir_list_append_IR(IR_content, cur_val_ir);
        //[GOTO label_false]
        IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
        cur_val_ir2->code_kind = IR_GOTO;
        cur_val_ir2->u.goto_st.place = label_false;
        ir_list_append_IR(IR_content, cur_val_ir2);
        return;
    }
    if (n->childs[1]->sname == tokens[_RELOP]) {
        //Exp RELOP Exp
        Operand t1 = IR_geneTMP_t();
        IR_Exp(n->childs[0], t1);
        Operand t2 = IR_geneTMP_t();
        IR_Exp(n->childs[2], t2);
        //[IF t1 op t2 GOTO label_true]
        IR* cur_val_ir = (IR*)malloc(sizeof(IR));
        cur_val_ir->code_kind = IR_IF;
        cur_val_ir->u.if_st.op1 = t1;
        cur_val_ir->u.if_st.op2 = t2;
        cur_val_ir->u.if_st.op = n->childs[1]->sval;
        cur_val_ir->u.if_st.desti = label_true;
        ir_list_append_IR(IR_content, cur_val_ir);
        //[GOTO label_false]
        IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
        cur_val_ir2->code_kind = IR_GOTO;
        cur_val_ir2->u.goto_st.place = label_false;
        ir_list_append_IR(IR_content, cur_val_ir2);
    } else if (n->childs[1]->sname == tokens[_AND]) {
        //Exp AND Exp
        Operand t1 = IR_geneTMP_v();
        IR_Cond(n->childs[0], t1, label_false);
        //[LABEL label1] 
        IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
        cur_val_ir2->code_kind = IR_LABEL;
        cur_val_ir2->u.label.label_name = t1;
        ir_list_append_IR(IR_content, cur_val_ir2);
        IR_Cond(n->childs[2], label_true, label_false);
    } else if (n->childs[1]->sname == tokens[_OR]) {
        //Exp OR Exp
        Operand t1 = IR_geneTMP_v();
        IR_Cond(n->childs[0], label_true, t1);
        //[LABEL label1] 
        IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
        cur_val_ir2->code_kind = IR_LABEL;
        cur_val_ir2->u.label.label_name = t1;
        ir_list_append_IR(IR_content, cur_val_ir2);
        IR_Cond(n->childs[2], label_true, label_false);
    } else if (n->childs[0]->sname == tokens[_NOT]) {
        IR_Cond(n->childs[1], label_false, label_true);
    } else {
        //other cases
        Operand t1 = IR_geneTMP_t();
        Operand zero = ir_Operand_init(IR_CONSTANT, "0");
        IR_Exp(n, t1);
        //[IF t1 != #0 GOTO label_true]
        IR* cur_val_ir = (IR*)malloc(sizeof(IR));
        cur_val_ir->code_kind = IR_IF;
        cur_val_ir->u.if_st.op1 = t1;
        cur_val_ir->u.if_st.op2 = zero;
        cur_val_ir->u.if_st.op = "!=";
        cur_val_ir->u.if_st.desti = label_true;
        ir_list_append_IR(IR_content, cur_val_ir);
        //[GOTO label_false]
        IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
        cur_val_ir2->code_kind = IR_GOTO;
        cur_val_ir2->u.goto_st.place = label_false;
        ir_list_append_IR(IR_content, cur_val_ir2);
    }
}


void IR_Exp(Snode* n, Operand catch) {
    if (n->childs[0]->sname == tokens[_INT]) {
        //INT
        if (catch) {
            Operand cur_val = ir_Operand_init(IR_CONSTANT, n->childs[0]->sval);
            IR* cur_val_ir = (IR*)malloc(sizeof(IR));
            cur_val_ir->code_kind = IR_ASSIGN;
            cur_val_ir->u.assign.left = catch;
            cur_val_ir->u.assign.right = cur_val;
            ir_list_append_IR(IR_content, cur_val_ir);
        }
    } else if (n->childs[0]->sname == tokens[_FLOAT]) {
        //FLOAT
        
    } else if (n->childs[0]->sname == tokens[_ID]) {
        if (n->childs_num == 1) {
            //ID
            if (catch) {
                Operand cur_val = ir_Operand_init(IR_VARIABLE, n->childs[0]->sval);
                IR* cur_val_ir = (IR*)malloc(sizeof(IR));
                cur_val_ir->code_kind = IR_ASSIGN;
                cur_val_ir->u.assign.left = catch;
                cur_val_ir->u.assign.right = cur_val;
                ir_list_append_IR(IR_content, cur_val_ir);
            }
        } else {
            if (n->childs_num == 3) {
                //ID  LP  RP
                if (catch) {
                    if (strcmp((n->childs[0]->sval), "read") == 0) {
                        IR* cur_val_ir = (IR*)malloc(sizeof(IR));
                        cur_val_ir->code_kind = IR_READ;
                        cur_val_ir->u.read.val = catch;
                        ir_list_append_IR(IR_content, cur_val_ir);
                    } else {
                        Operand cur_val = ir_Operand_init(IR_VARIABLE, n->childs[0]->sval);
                        IR* cur_val_ir = (IR*)malloc(sizeof(IR));
                        cur_val_ir->code_kind = IR_CALL;
                        cur_val_ir->u.call.func = cur_val;
                        cur_val_ir->u.call.ret = catch;
                        ir_list_append_IR(IR_content, cur_val_ir);
                    }
                }
            } else {
                //ID  LP  Args RP
                Operand* argsOps = NULL;
                int length = 0;
                IR_Args(n->childs[2], &argsOps, 0, &length);
                if (strcmp((n->childs[0]->sval), "write") == 0) {
                    IR* cur_val_ir = (IR*)malloc(sizeof(IR));
                    cur_val_ir->code_kind = IR_WRITE;
                    cur_val_ir->u.write.val = argsOps[0];
                    ir_list_append_IR(IR_content, cur_val_ir);
                    if (catch) {
                        Operand cur_val = ir_Operand_init(IR_CONSTANT, "0");
                        cur_val_ir = (IR*)malloc(sizeof(IR));
                        cur_val_ir->code_kind = IR_ASSIGN;
                        cur_val_ir->u.assign.left = catch;
                        cur_val_ir->u.assign.right = cur_val;
                        ir_list_append_IR(IR_content, cur_val_ir);
                    }
                } else {
                    IR* cur_val_ir = NULL;
                    for (int i = length - 1; i >= 0; i--) {
                        cur_val_ir = (IR*)malloc(sizeof(IR));
                        cur_val_ir->code_kind = IR_ARG;
                        cur_val_ir->u.param.val = argsOps[i];
                        ir_list_append_IR(IR_content, cur_val_ir);
                    }
                    Operand cur_val = ir_Operand_init(IR_VARIABLE, n->childs[0]->sval);
                    cur_val_ir = (IR*)malloc(sizeof(IR));
                    cur_val_ir->code_kind = IR_CALL;
                    cur_val_ir->u.call.func = cur_val;
                    cur_val_ir->u.call.ret = catch;
                    ir_list_append_IR(IR_content, cur_val_ir);
                }
            }
        }
    } else if (n->childs[0]->sname == tokens[_MINUS]) {
        //MINUS Exp
        if (catch) {
            Operand t1 = IR_geneTMP_t();
            IR_Exp(n->childs[1], t1);
            Operand zero = ir_Operand_init(IR_CONSTANT, "0");
            IR* cur_val_ir1 = (IR*)malloc(sizeof(IR));
            cur_val_ir1->code_kind = IR_SUB;
            cur_val_ir1->u.op3.op1 = zero;
            cur_val_ir1->u.op3.op2 = t1;
            cur_val_ir1->u.op3.result = catch;
            ir_list_append_IR(IR_content, cur_val_ir1);
        } else {
            IR_Exp(n->childs[1], NULL);
        }
    } else if (n->childs[0]->sname == tokens[_NOT]) {
        //NOT Exp
        if (catch) {
            Operand v1 = IR_geneTMP_v();
            Operand v2 = IR_geneTMP_v();
            Operand zero = ir_Operand_init(IR_CONSTANT, "0");
            Operand one = ir_Operand_init(IR_CONSTANT, "1");
            // [place := #0]
            IR* cur_val_ir1 = (IR*)malloc(sizeof(IR));
            cur_val_ir1->code_kind = IR_ASSIGN;
            cur_val_ir1->u.assign.left = catch;
            cur_val_ir1->u.assign.right = zero;
            ir_list_append_IR(IR_content, cur_val_ir1);
            // IR_Cond
            IR_Cond(n, v1, v2);
            // [LABEL label1]
            IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
            cur_val_ir2->code_kind = IR_LABEL;
            cur_val_ir2->u.label.label_name = v1;
            ir_list_append_IR(IR_content, cur_val_ir2);
            // [place := #1]
            IR* cur_val_ir3 = (IR*)malloc(sizeof(IR));
            cur_val_ir3->code_kind = IR_ASSIGN;
            cur_val_ir3->u.assign.left = catch;
            cur_val_ir3->u.assign.right = one;
            ir_list_append_IR(IR_content, cur_val_ir3);
            // [LABEL label2]
            IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
            cur_val_ir4->code_kind = IR_LABEL;
            cur_val_ir4->u.label.label_name = v2;
            ir_list_append_IR(IR_content, cur_val_ir4);
        } else {
            IR_Exp(n->childs[1], NULL);
        }
    } else if (n->childs[0]->sname == tokens[_LP] && n->childs[2]->sname == tokens[_RP]) {
        //LP   Exp  RP
        IR_Exp(n->childs[1], catch);
    } else if (n->childs_num == 3) {
        if (n->childs[0]->sname == nontokens[_Exp] && n->childs[2]->sname == nontokens[_Exp]) {
            TYPE_CMM* t1 = ExprAnalysis(n->childs[0]);
            TYPE_CMM* t3 = ExprAnalysis(n->childs[2]);
            int       isEqT = typeJudgeEquel(t1, t3);
            if (n->childs[1]->sname == tokens[_ASSIGNOP]) {
                //Exp ASSIGNOP Exp
                if (n->childs[0]->childs_num == 1 && n->childs[0]->childs[0]->sname == tokens[_ID]) {
                    // Operand t1 = IR_geneTMP_t();
                    // IR_Exp(n->childs[2], t1);
                    // Operand left_val = ir_Operand_init(IR_VARIABLE, n->childs[0]->childs[0]->sval);
                    // //left_val = t1
                    // IR* cur_val_ir1 = (IR*)malloc(sizeof(IR));
                    // cur_val_ir1->code_kind = IR_ASSIGN;
                    // cur_val_ir1->u.assign.left = left_val;
                    // cur_val_ir1->u.assign.right = t1;
                    // ir_list_append_IR(IR_content, cur_val_ir1);
                    Operand left_val = ir_Operand_init(IR_VARIABLE, n->childs[0]->childs[0]->sval);
                    IR_Exp(n->childs[2], left_val);
                    if (catch) {
                        //catch = left_val
                        IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
                        cur_val_ir2->code_kind = IR_ASSIGN;
                        cur_val_ir2->u.assign.left = catch;
                        cur_val_ir2->u.assign.right = left_val;
                        ir_list_append_IR(IR_content, cur_val_ir2);
                    } 
                } 
                // else if (n->childs[2]->childs_num == 4 && n->childs[2]->childs[0]->sname == nontokens[_Exp]
                //             && n->childs[2]->childs[2]->sname == nontokens[_Exp]) {
                //     //Exp           ASSIGNOP          Exp
                //     // \_ Exp LB Exp RB                \_ Exp LB Exp RB     
                //     //      \_  ID                          \_ ID
                //     char* cur_ID = n->childs[2]->childs[0]->childs[0]->sval;
                //     Operand ret_p = IR_geneTMP_t();
                //     Operand cur_p = ir_Operand_init(IR_GET_ADDR, cur_ID);
                //     // [ret_p := &cur_p]
                //     IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
                //     cur_val_ir4->code_kind = IR_ASSIGN;
                //     cur_val_ir4->u.assign.left = ret_p;
                //     cur_val_ir4->u.assign.right = cur_p;
                //     ir_list_append_IR(IR_content, cur_val_ir4);
                //     // [size := Exp]
                //     Operand size = IR_geneTMP_t();
                //     IR_Exp(n->childs[2]->childs[2], size);
                //     // [four_star := 4 * size]
                //     Operand four_star = IR_geneTMP_t();
                //     Operand four = ir_Operand_init(IR_CONSTANT, "4");
                //     cur_val_ir4 = (IR*)malloc(sizeof(IR));
                //     cur_val_ir4->code_kind = IR_MUL;
                //     cur_val_ir4->u.op3.op1 = four;
                //     cur_val_ir4->u.op3.op2 = size;
                //     cur_val_ir4->u.op3.result = four_star;
                //     ir_list_append_IR(IR_content, cur_val_ir4);
                //     // [to_access := ret_p + four_star]
                //     Operand to_access = IR_geneTMP_t();
                //     cur_val_ir4 = (IR*)malloc(sizeof(IR));
                //     cur_val_ir4->code_kind = IR_ADD;
                //     cur_val_ir4->u.op3.op1 = ret_p;
                //     cur_val_ir4->u.op3.op2 = four_star;
                //     cur_val_ir4->u.op3.result = to_access;
                //     ir_list_append_IR(IR_content, cur_val_ir4);
                //     // [tmp := *to_access]
                //     Operand tmp = IR_geneTMP_t();
                //     Operand to_access_tmp = (Operand)malloc(sizeof(struct Operand_));
                //     to_access_tmp->var_str = to_access->var_str;
                //     to_access_tmp->opr_kind = IR_DE_REF;
                //     cur_val_ir4 = (IR*)malloc(sizeof(IR));
                //     cur_val_ir4->code_kind = IR_ASSIGN;
                //     cur_val_ir4->u.assign.left = tmp;
                //     cur_val_ir4->u.assign.right = to_access_tmp;
                //     ir_list_append_IR(IR_content, cur_val_ir4);
                //     //
                //     //
                //     //Exp           ASSIGNOP          Exp
                //     // \_ Exp LB Exp RB                \_ Exp LB Exp RB     
                //     //      \_  ID                          \_ ID
                //     char* cur_ID_left = n->childs[0]->childs[0]->childs[0]->sval;
                //     Operand ret_p2 = IR_geneTMP_t();
                //     Operand cur_p2 = ir_Operand_init(IR_GET_ADDR, cur_ID_left);
                //     // [ret_p2 := &cur_p2]
                //     cur_val_ir4 = (IR*)malloc(sizeof(IR));
                //     cur_val_ir4->code_kind = IR_ASSIGN;
                //     cur_val_ir4->u.assign.left = ret_p2;
                //     cur_val_ir4->u.assign.right = cur_p2;
                //     ir_list_append_IR(IR_content, cur_val_ir4);
                //     // [size := Exp]
                //     Operand size2 = IR_geneTMP_t();
                //     IR_Exp(n->childs[0]->childs[2], size2);
                //     // [four_star2 := 4 * size]
                //     Operand four_star2 = IR_geneTMP_t();
                //     cur_val_ir4 = (IR*)malloc(sizeof(IR));
                //     cur_val_ir4->code_kind = IR_MUL;
                //     cur_val_ir4->u.op3.op1 = four;
                //     cur_val_ir4->u.op3.op2 = size2;
                //     cur_val_ir4->u.op3.result = four_star2;
                //     ir_list_append_IR(IR_content, cur_val_ir4);
                //     // [to_access2 := ret_p2 + four_star2]
                //     Operand to_access2 = IR_geneTMP_t();
                //     cur_val_ir4 = (IR*)malloc(sizeof(IR));
                //     cur_val_ir4->code_kind = IR_ADD;
                //     cur_val_ir4->u.op3.op1 = ret_p2;
                //     cur_val_ir4->u.op3.op2 = four_star2;
                //     cur_val_ir4->u.op3.result = to_access2;
                //     ir_list_append_IR(IR_content, cur_val_ir4);
                //     // [*to_access2 = tmp]
                //     Operand to_access2_ = (Operand)malloc(sizeof(struct Operand_));
                //     to_access2_->opr_kind = IR_DE_REF;
                //     to_access2_->var_str = to_access2->var_str;
                //     cur_val_ir4 = (IR*)malloc(sizeof(IR));
                //     cur_val_ir4->code_kind = IR_ASSIGN;
                //     cur_val_ir4->u.assign.left = to_access2_;
                //     cur_val_ir4->u.assign.right = tmp;
                //     ir_list_append_IR(IR_content, cur_val_ir4);
                //} 
                else {
                    //Exp ASSIGNOP Exp
                    // \_ Exp LB Exp RB
                    //      \_  ID
                    Operand right = IR_geneTMP_t();
                    IR_Exp(n->childs[2], right);
                    char* cur_ID = n->childs[0]->childs[0]->childs[0]->sval;

                    Operand cur_p = ir_Operand_init(IR_VARIABLE, cur_ID);
                    // [size := Exp]
                    Operand size = IR_geneTMP_t();
                    IR_Exp(n->childs[0]->childs[2], size);
                    // [four_star := 4 * size]
                    Operand four_star = IR_geneTMP_t();
                    Operand four = ir_Operand_init(IR_CONSTANT, "4");
                    IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
                    cur_val_ir4->code_kind = IR_MUL;
                    cur_val_ir4->u.op3.op1 = four;
                    cur_val_ir4->u.op3.op2 = size;
                    cur_val_ir4->u.op3.result = four_star;
                    ir_list_append_IR(IR_content, cur_val_ir4);
                    // [to_access := cur_p + four_star]
                    Operand to_access = IR_geneTMP_t();
                    cur_val_ir4 = (IR*)malloc(sizeof(IR));
                    cur_val_ir4->code_kind = IR_ADD;
                    cur_val_ir4->u.op3.op1 = cur_p;
                    cur_val_ir4->u.op3.op2 = four_star;
                    cur_val_ir4->u.op3.result = to_access;
                    ir_list_append_IR(IR_content, cur_val_ir4);
                    // [*to_access = right]
                    Operand to_access2 = (Operand)malloc(sizeof(struct Operand_));
                    to_access2->var_str = to_access->var_str;
                    to_access2->opr_kind = IR_DE_REF;
                    cur_val_ir4 = (IR*)malloc(sizeof(IR));
                    cur_val_ir4->code_kind = IR_ASSIGN;
                    cur_val_ir4->u.assign.left = to_access2;
                    cur_val_ir4->u.assign.right = right;
                    ir_list_append_IR(IR_content, cur_val_ir4);
                }
            } else {
                //Exp ? Exp
                if (n->childs[1]->sname == tokens[_PLUS] || n->childs[1]->sname == tokens[_MINUS] 
                        || n->childs[1]->sname == tokens[_STAR] || n->childs[1]->sname == tokens[_DIV]) {
                    if (catch) {
                        Operand t1 = IR_geneTMP_t();
                        IR_Exp(n->childs[0], t1);
                        Operand t2 = IR_geneTMP_t();
                        IR_Exp(n->childs[2], t2);
                        IR* cur_val_ir = (IR*)malloc(sizeof(IR));
                        if (n->childs[1]->sname == tokens[_PLUS]) {
                            cur_val_ir->code_kind = IR_ADD;
                        } else if (n->childs[1]->sname == tokens[_MINUS]) {
                            cur_val_ir->code_kind = IR_SUB;
                        } else if (n->childs[1]->sname == tokens[_STAR]) {
                            cur_val_ir->code_kind = IR_MUL;
                        } else if (n->childs[1]->sname == tokens[_DIV]) {
                            cur_val_ir->code_kind = IR_DIV;
                        } 
                        cur_val_ir->u.op3.op1 = t1;
                        cur_val_ir->u.op3.op2 = t2;
                        cur_val_ir->u.op3.result = catch;
                        ir_list_append_IR(IR_content, cur_val_ir);
                    } else {
                        IR_Exp(n->childs[0], NULL);
                        IR_Exp(n->childs[2], NULL);
                    }
                    
                } else {
                    if (catch) {
                        Operand v1 = IR_geneTMP_v();
                        Operand v2 = IR_geneTMP_v();
                        Operand zero = ir_Operand_init(IR_CONSTANT, "0");
                        Operand one = ir_Operand_init(IR_CONSTANT, "1");
                        // [place := #0]
                        IR* cur_val_ir1 = (IR*)malloc(sizeof(IR));
                        cur_val_ir1->code_kind = IR_ASSIGN;
                        cur_val_ir1->u.assign.left = catch;
                        cur_val_ir1->u.assign.right = zero;
                        ir_list_append_IR(IR_content, cur_val_ir1);
                        // IR_Cond
                        IR_Cond(n, v1, v2);
                        // [LABEL label1]
                        IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
                        cur_val_ir2->code_kind = IR_LABEL;
                        cur_val_ir2->u.label.label_name = v1;
                        ir_list_append_IR(IR_content, cur_val_ir2);
                        // [place := #1]
                        IR* cur_val_ir3 = (IR*)malloc(sizeof(IR));
                        cur_val_ir3->code_kind = IR_ASSIGN;
                        cur_val_ir3->u.assign.left = catch;
                        cur_val_ir3->u.assign.right = one;
                        ir_list_append_IR(IR_content, cur_val_ir3);
                        // [LABEL label2]
                        IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
                        cur_val_ir4->code_kind = IR_LABEL;
                        cur_val_ir4->u.label.label_name = v2;
                        ir_list_append_IR(IR_content, cur_val_ir4);
                    } else {
                        IR_Exp(n->childs[0], NULL);
                        IR_Exp(n->childs[2], NULL);
                    }
                }
            }
        } else {
            //Exp DOT ID
            
        }
    } else {
        //Exp LB Exp RB
        //   \_  ID
        char* cur_ID = n->childs[0]->childs[0]->sval;
        Operand cur_p = ir_Operand_init(IR_VARIABLE, cur_ID);
        // [size := Exp]
        Operand size = IR_geneTMP_t();
        IR_Exp(n->childs[2], size);
        // [four_star := 4 * size]
        Operand four_star = IR_geneTMP_t();
        Operand four = ir_Operand_init(IR_CONSTANT, "4");
        IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
        cur_val_ir4->code_kind = IR_MUL;
        cur_val_ir4->u.op3.op1 = four;
        cur_val_ir4->u.op3.op2 = size;
        cur_val_ir4->u.op3.result = four_star;
        ir_list_append_IR(IR_content, cur_val_ir4);
        // [to_access := ret_p + four_star]
        Operand to_access = IR_geneTMP_t();
        cur_val_ir4 = (IR*)malloc(sizeof(IR));
        cur_val_ir4->code_kind = IR_ADD;
        cur_val_ir4->u.op3.op1 = cur_p;
        cur_val_ir4->u.op3.op2 = four_star;
        cur_val_ir4->u.op3.result = to_access;
        ir_list_append_IR(IR_content, cur_val_ir4);
        // [catch := *to_access]
        Operand to_access2 = (Operand)malloc(sizeof(struct Operand_));
        to_access2->var_str = to_access->var_str;
        to_access2->opr_kind = IR_DE_REF;
        cur_val_ir4 = (IR*)malloc(sizeof(IR));
        cur_val_ir4->code_kind = IR_ASSIGN;
        cur_val_ir4->u.assign.left = catch;
        cur_val_ir4->u.assign.right = to_access2;
        ir_list_append_IR(IR_content, cur_val_ir4);
    }
}

void IR_VarList(Snode* node) {
    //                           VarList -> ParamDec COMMA VarList | ParamDec
    //                                      ParamDec -> Specifier VarDec
    //                                                            VarDec -> ID | VarDec LB INT RB 
    Snode* curVar = node->childs[0]->childs[1];
    while (curVar->childs_num == 4) {
        curVar = curVar->childs[0];
    }
    Operand cur_val = ir_Operand_init(IR_VARIABLE, curVar->childs[0]->sval);
    IR* cur_val_ir = (IR*)malloc(sizeof(IR));
    cur_val_ir->code_kind = IR_PARAM;
    cur_val_ir->u.param.val = cur_val;
    ir_list_append_IR(IR_content, cur_val_ir);
    if (node->childs_num == 3) {
        IR_VarList(node->childs[2]);
    }
}

void IR_Dec(Snode* node) {
    //Dec -> VarDec | VarDec ASSIGNOP Exp
    //       VarDec -> ID | VarDec LB INT RB
    //                      VarDec -> ID
    if (node->childs[0]->childs_num == 1) {
        //Var
        if (node->childs_num == 3) {
            char* curID = node->childs[0]->childs[0]->sval;
            Operand cur_val = ir_Operand_init(IR_VARIABLE, curID);
            IR_Exp(node->childs[2], cur_val);
        }
    } else {
        //1-d-array
        char* curID = node->childs[0]->childs[0]->childs[0]->sval;
        Operand curIDOp = ir_Operand_init(IR_VARIABLE, curID);
        Operand curIDOp_tmp = ir_Operand_init(IR_VARIABLE, curID);
        char* new_str_tmp = (char*)malloc(sizeof(char) * 15);
        strcpy(new_str_tmp, curIDOp_tmp->var_str);
        curIDOp_tmp->var_str = new_str_tmp;
        strcat(curIDOp_tmp->var_str, "_tmp");
        char* curNUM = node->childs[0]->childs[2]->sval;
        int num = atoi(curNUM);
        num *= 4;
        char* four_star_NUM_str = (char*)malloc(sizeof(char) * 20);
        sprintf(four_star_NUM_str, "%d", num);
        Operand curNUMOp = ir_Operand_init(IR_VARIABLE, four_star_NUM_str);
        //[DEC curID [curNUMOp]]
        IR* cur_val_ir = (IR*)malloc(sizeof(IR));
        cur_val_ir->code_kind = IR_DEC;
        cur_val_ir->u.dec.opr = curIDOp_tmp;
        cur_val_ir->u.dec.size = curNUMOp;
        ir_list_append_IR(IR_content, cur_val_ir);
        //[curID = &curID]
        Operand curNUMOp_de = ir_Operand_init(IR_GET_ADDR, curIDOp_tmp->var_str);
        cur_val_ir = (IR*)malloc(sizeof(IR));
        cur_val_ir->code_kind = IR_ASSIGN;
        cur_val_ir->u.assign.left = curIDOp;
        cur_val_ir->u.assign.right = curNUMOp_de;
        ir_list_append_IR(IR_content, cur_val_ir);
    }
}

void IR_DecList(Snode* node) {
    //DecList -> Dec | Dec COMMA DecList
    IR_Dec(node->childs[0]);
    if (node->childs_num > 1) {
        IR_DecList(node->childs[2]);
    }
}

void IR_DefList(Snode* node) {
    //             DefList -> Def DefList | e
    //                        Def -> Specifier DecList SEMI
    if (node == NULL) {
        return;
    }
    //Def -> Specifier DecList SEMI
    IR_DecList(node->childs[0]->childs[1]);
    IR_DefList(node->childs[1]);
}

void IR_Stmt(Snode* node) {
    if (node->childs[0]->sname == nontokens[_Exp]) {
        //Exp SEMI
        IR_Exp(node->childs[0], NULL);
    } else if (node->childs[0]->sname == tokens[_RETURN]) {
        //RETURN Exp SEMI
        Operand v1 = IR_geneTMP_v();
        IR_Exp(node->childs[1], v1);
        IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
        cur_val_ir4->code_kind = IR_RETURN;
        cur_val_ir4->u.return_st.val = v1;
        ir_list_append_IR(IR_content, cur_val_ir4);
    } else if (node->childs[0]->sname == nontokens[_CompSt]) {
        //CompSt
        IR_CompSt(node->childs[0]);
    } else if (node->childs_num == 5) {
        if (node->childs[0]->sname == tokens[_IF]) {
            //IF LP Exp RP Stmt
            Operand v1 = IR_geneTMP_v();
            Operand v2 = IR_geneTMP_v();
            IR_Cond(node->childs[2], v1, v2);
            //  [LABEL label1]
            IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
            cur_val_ir2->code_kind = IR_LABEL;
            cur_val_ir2->u.label.label_name = v1;
            ir_list_append_IR(IR_content, cur_val_ir2);
            // code
            IR_Stmt(node->childs[4]);
            // [LABEL label2]
            IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
            cur_val_ir4->code_kind = IR_LABEL;
            cur_val_ir4->u.label.label_name = v2;
            ir_list_append_IR(IR_content, cur_val_ir4);
        } else {
            //WHILE LP Exp RP Stmt
            Operand v1 = IR_geneTMP_v();
            Operand v2 = IR_geneTMP_v();
            Operand v3 = IR_geneTMP_v();
            // [LABEL label1]
            IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
            cur_val_ir2->code_kind = IR_LABEL;
            cur_val_ir2->u.label.label_name = v1;
            ir_list_append_IR(IR_content, cur_val_ir2);
            // code1
            IR_Cond(node->childs[2], v2, v3);
            // [LABEL label2]
            IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
            cur_val_ir4->code_kind = IR_LABEL;
            cur_val_ir4->u.label.label_name = v2;
            ir_list_append_IR(IR_content, cur_val_ir4);
            // code2
            IR_Stmt(node->childs[4]);
            // [GOTO label1]
            IR* cur_val_ir5 = (IR*)malloc(sizeof(IR));
            cur_val_ir5->code_kind = IR_GOTO;
            cur_val_ir5->u.goto_st.place = v1;
            ir_list_append_IR(IR_content, cur_val_ir5);
            // [LABEL label3]
            IR* cur_val_ir3 = (IR*)malloc(sizeof(IR));
            cur_val_ir3->code_kind = IR_LABEL;
            cur_val_ir3->u.label.label_name = v3;
            ir_list_append_IR(IR_content, cur_val_ir3);
        }
    } else {
        //IF LP Exp RP Stmt ELSE Stmt
        Operand v1 = IR_geneTMP_v();
        Operand v2 = IR_geneTMP_v();
        Operand v3 = IR_geneTMP_v();
        // code1
        IR_Cond(node->childs[2], v1, v2);
        // [LABEL label1]
        IR* cur_val_ir2 = (IR*)malloc(sizeof(IR));
        cur_val_ir2->code_kind = IR_LABEL;
        cur_val_ir2->u.label.label_name = v1;
        ir_list_append_IR(IR_content, cur_val_ir2);
        // code2
        IR_Stmt(node->childs[4]);
        // [GOTO label3]
        IR* cur_val_ir5 = (IR*)malloc(sizeof(IR));
        cur_val_ir5->code_kind = IR_GOTO;
        cur_val_ir5->u.goto_st.place = v3;
        ir_list_append_IR(IR_content, cur_val_ir5);
        // [LABEL label2]
        IR* cur_val_ir4 = (IR*)malloc(sizeof(IR));
        cur_val_ir4->code_kind = IR_LABEL;
        cur_val_ir4->u.label.label_name = v2;
        ir_list_append_IR(IR_content, cur_val_ir4);
        // code3
        IR_Stmt(node->childs[6]);
        // [LABEL label3]
        IR* cur_val_ir3 = (IR*)malloc(sizeof(IR));
        cur_val_ir3->code_kind = IR_LABEL;
        cur_val_ir3->u.label.label_name = v3;
        ir_list_append_IR(IR_content, cur_val_ir3);
    }
}


void IR_StmtList(Snode* node) {
    //             StmtList -> Stmt StmtList
    //                         Stmt -> Exp SEMI |
    //                                 CompSt
    //                                 RETURN Exp SEMI
    //                                 IF LP Exp RP Stmt
    //                                 IF LP Exp RP Stmt ELSE Stmt
    //                                 WHILE LP Exp RP Stmt
    if (node == NULL) {
        return;
    }
    IR_Stmt(node->childs[0]);
    IR_StmtList(node->childs[1]);
}

void IR_CompSt(Snode* node) {
    //CompSt -> LC DefList StmtList RC
    //             DefList -> Def DefList
    //                        Def -> Specifier DecList SEMI
    //             StmtList -> Stmt StmtList
    //                         Stmt -> Exp SEMI |
    //                                 CompSt
    //                                 RETURN Exp SEMI
    //                                 IF LP Exp RP Stmt
    //                                 IF LP Exp RP Stmt ELSE Stmt
    //                                 WHILE LP Exp RP Stmt
    IR_DefList(node->childs[1]);
    IR_StmtList(node->childs[2]);
}

void IR_ExtDef(Snode* node) {
    if (node->childs_num == 2) {
        //Specifier SEMI
        
    } else if (node->childs[1]->sname == nontokens[_FunDec]) {
        //Specifier FunDec CompSt
        //          FunDec -> ID LP (VarList) RP
        //                           VarList -> ParamDec COMMA VarList | ParamDec
        //                                      ParamDec -> Specifier VarDec
        //                                                            VarDec -> ID | VarDec LB INT RB 
        char* funName = node->childs[1]->childs[0]->sval;
        // 1. add FUNCTION XXX :
        Operand funNameOp = ir_Operand_init(IR_VARIABLE, funName);
        IR* funcDecIR = (IR*)malloc(sizeof(IR));
        funcDecIR->code_kind = IR_FUNC;
        funcDecIR->u.func.func_name = funNameOp;
        ir_list_append_IR(IR_content, funcDecIR);
        // 2. add PARAM
        if (node->childs[1]->childs_num == 4) {
            IR_VarList(node->childs[1]->childs[2]);
        }
        // 3. add CompSt
        IR_CompSt(node->childs[2]);
    } else {
        //Specifier ExtDecList SEMI
        
    }
}



void startIR(LIST* symbolList, structLIST* structList, funcLIST* funcDefList,
             Snode** ExtDefs, unsigned int ExtDefsNum, char*  ir_filename) {
    IR_content = ir_list_init();
    for (unsigned int i = 0; i < ExtDefsNum; i++) {
        IR_ExtDef(ExtDefs[i]);
    }
    ir_write_to_file(IR_content, ir_filename);
}


#endif