#ifndef ENSTROPHY_H
#define ENSTROPHY_H

#include "amr-wind/CFDSim.H"
#include "amr-wind/utilities/PostProcessing.H"

namespace amr_wind {
namespace enstrophy {

/** enstrophy object
 *  \ingroup Enstrophy
 *
 *  A concrete impelementation of the post-processing interface that deals with
 *  the total enstrophy
 *
 */
class Enstrophy : public PostProcessBase::Register<Enstrophy>
{
public:
    static const std::string identifier() { return "Enstrophy"; }

    Enstrophy(CFDSim&, const std::string&);

    ~Enstrophy();

    //! Perform actions before mesh is created
    void pre_init_actions() override {}

    //! Read user inputs and create the different data probe instances
    void initialize() override;

    //! Interpolate fields at a given timestep and output to disk
    void post_advance_work() override;

    void post_regrid_actions() override {}

    //! calculate the L2 norm of a given field and component
    amrex::Real calculate_enstrophy();

private:
    //! prepare ASCII file and directory
    void prepare_ascii_file();

    //! Output sampled data in ASCII format
    void write_ascii();

    //! store the total enstrophy
    amrex::Real m_total_enstrophy;

    //! Reference to the CFD sim
    CFDSim& m_sim;

    /** Name of this sampling object.
     *
     *  The label is used to read user inputs from file and is also used for
     *  naming files directories depending on the output format.
     */
    const std::string m_label;

    //! reference to velocity
    const Field& m_velocity;
    //! reference to density
    const Field& m_density;

    //! filename for ASCII output
    std::string m_out_fname;

    //! Frequency of data sampling and output
    int m_out_freq{10};

    //! width in ASCII output
    int m_width{18};

    //! precision in ASCII output
    int m_precision{12};
};

} // namespace enstrophy
} // namespace amr_wind

#endif /* ENSTROPHY_H */
