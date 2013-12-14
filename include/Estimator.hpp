#ifndef ESTIMATOR_H
#define ESTIMATOR_H

#include <cstddef>
#include <vector>

static const size_t MAX_FRAMES_ESTIMATOR=100;

/** A simple circular buffer, based on a std::vector
 */
template < typename T >
class CircularVector
{
public:
    CircularVector(size_t size = 20) : idx(0), size(size)
    {
        data = std::vector<T>();
        data.reserve(size);
    }
    void push_back(const T& elt)
    {
        // first fill the vector, then 'rotate'
        if (data.size() < size) 
            data.push_back(elt);
        else
            data[ idx++ % size ] = elt;
    }

    std::vector<T> data;

private:
    uint idx;
    size_t size;
};


template < typename T >
class Estimator {

public:

    /** Creates a 'stupid' estimator that returns averaged value over several measurements
     *
     * \param gain: allows to adjust how damped the estimation is. High gains
     * lead to more responsive estimation, closer to observation, but less filtered.
     * A value of 1.0 means 'no estimation'. Low gains lead to smoother results, but
     * introduce delay. Minimum gain (0.0) means that the next estimated value is 
     * the average of the last MAX_FRAMES_ESTIMATOR measurements.
     */
    Estimator(float gain = .5) : gain(gain),
                                 length(MAX_FRAMES_ESTIMATOR * (1-gain) + 1),
                                 dirty(true) 
    {
        vals = CircularVector<T>(length);
    }

    /**
     * Adds an observed value to the estimator
     */
    void operator<<(const T& elt)
    {
        // max gain -> no filtering! just return last measurement
        if (gain >= 1.0) {
            last_val = elt;
            dirty = false;
            return;
        }

        vals.push_back(elt);
        dirty = true;
    }

    /**
     * Returns the estimated value
     */
    T operator()() const
    {
        // recompute the estimate only if the estimator is 'dirty', ie
        // new observed values have been provided.
        if (dirty) last_val = mean();
        return last_val;
    }

    T mean() const
    {
        size_t nbvals = vals.data.size();

        // clone() is required here because cv::Mat assignment does *not*
        // copy the data, but merely a pointer to it
        T sum = vals.data[0].clone();
        for(uint i = 1 ; i < nbvals ; ++i) sum += vals.data[i];
        return sum/nbvals;
    }

    T variance() const
    {
        T current_mean = mean();

        // clone() is required here because cv::Mat assignment does *not*
        // copy the data, but merely a pointer to it
         T temp = (current_mean-vals.data[0])*(current_mean-vals.data[0]).clone();
        for(uint i = 1 ; i < vals.data.size() ; ++i)
            temp += (current_mean-vals.data[i])*(current_mean-vals.data[i]);
        return temp/length;
    }

protected:
    CircularVector<T> vals;
    mutable T last_val;
    bool dirty;
    size_t length;
    float gain;
};


#endif
