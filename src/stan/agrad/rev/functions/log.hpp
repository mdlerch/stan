#ifndef STAN__AGRAD__REV__FUNCTIONS__LOG_HPP
#define STAN__AGRAD__REV__FUNCTIONS__LOG_HPP

#include <cmath>
#include <stan/agrad/rev/var.hpp>
#include <stan/agrad/rev/internal/v_vari.hpp>

namespace stan {
  namespace agrad {

    namespace {
      class log_vari : public op_v_vari {
      public:
        log_vari(vari* avi) :
          op_v_vari(std::log(avi->val_),avi) {
        }
        void chain() {
          avi_->adj_ += adj_ / avi_->val_;
        }
      };
    }

    /**
     * Return the natural log of the specified variable (cmath).
     *
     * The derivative is defined by
     *
     * \f$\frac{d}{dx} \log x = \frac{1}{x}\f$.
     *
       \f[
       \mbox{log}(x) = 
       \begin{cases}
         \textrm{NaN} & \mbox{if } x < 0\\
         \ln(x) & \mbox{if } x \geq 0 \\[6pt]
         \textrm{NaN} & \mbox{if } x = \textrm{NaN}
       \end{cases}
       \f]
       
       \f[
       \frac{\partial\,\mbox{log}(x)}{\partial x} = 
       \begin{cases}
         \textrm{NaN} & \mbox{if } x < 0\\
         \frac{1}{x} & \mbox{if } x\geq 0 \\[6pt]
         \textrm{NaN} & \mbox{if } x = \textrm{NaN}
       \end{cases}
       \f]
     *
     * @param a Variable whose log is taken.
     * @return Natural log of variable.
     */
    inline var log(const var& a) {
      return var(new log_vari(a.vi_));
    }
    
  }
}
#endif
