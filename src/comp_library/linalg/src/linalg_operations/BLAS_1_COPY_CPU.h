//-*-C++-*-

#ifndef LINALG_COPY_CPU_H
#define LINALG_COPY_CPU_H

namespace LIN_ALG {

  template<>
  class COPY<CPU>
  {
  public:

    template<typename scalartype>
    static void row(matrix<scalartype, CPU>& X, int xi, matrix<scalartype, CPU>& Y, int yi,
                    int /*thread_id*/, int /*stream_id*/)
    {

      assert(xi>-1 && xi<X.size().first);
      assert(yi>-1 && yi<Y.size().first);

      assert(X.size().second == Y.size().second);

      execute(X.size().second, X.ptr(xi,0), X.leadingDimension(), Y.ptr(yi,0), Y.leadingDimension());
    }

    template<typename scalartype>
    static void col(matrix<scalartype, CPU>& X, int xi, matrix<scalartype, CPU>& Y, int yi,
                    int /*thread_id*/, int /*stream_id*/)
    {
      assert(xi>-1 && xi<X.size().second);
      assert(yi>-1 && yi<Y.size().second);
      assert(X.size().first == Y.size().first);

      dca::linalg::blas::copy(X.size().first, X.ptr(0,xi), 1, Y.ptr(0,yi), 1);
    }

    template<typename scalartype>
    inline static void many_rows(int N_x, int N_i, int* i_x, scalartype* x, int inc_x, int* i_y, scalartype* y, int inc_y,
                                 int /*thread_id*/, int /*stream_id*/)
    {
      for(int i=0; i<N_x; ++i)
        for(int l=0; l<N_i; ++l)
          y[i_y[l]+i*inc_y] = x[i_x[l]+i*inc_x];
    }

    template<typename scalartype>
    inline static void many_columns(int N_x, int N_i, int* i_x, scalartype* x, int inc_x, int* i_y, scalartype* y, int inc_y,
                                    int /*thread_id*/, int /*stream_id*/)
    {
      for(int l=0; l<N_i; ++l)
        for(int i=0; i<N_x; ++i)
          y[i+i_y[l]*inc_y] = x[i+i_x[l]*inc_x];
    }
  };

}

#endif
